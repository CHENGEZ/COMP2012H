#include "gitlite.h"
#include "Utils.h"
#define DEBUG 0
using namespace std;

const string msg_initial_commit = "initial commit";

const string msg_no_changes_added = "No changes added to the commit.";

const string msg_no_reason_remove = "No reason to remove the file.";

const string msg_commit_does_not_exist = "No commit with that id exists.";

const string msg_file_does_not_exist = "File does not exist in that commit.";

const string msg_untracked_file = "There is an untracked file in the way; delete it, or add and commit it first.";

const string msg_branch_does_not_exist = "A branch with that name does not exist.";

const string msg_checkout_current = "No need to checkout the current branch.";

const string msg_branch_exists = "A branch with that name already exists.";

const string msg_remove_current = "Cannot remove the current branch.";

const string msg_merge_current = "Cannot merge a branch with itself.";

const string msg_exists_uncommitted_changes = "You have uncommitted changes.";

const string msg_given_is_ancestor_of_current = "Given branch is an ancestor of the current branch.";

const string msg_fast_forward = "Current branch fast-forwarded.";

const string msg_encountered_merge_conflict = "Encountered a merge conflict.";

const string status_branches_header = "=== Branches ===";

const string status_staged_files_header = "=== Staged Files ===";

const string status_removed_files_header = "=== Removed Files ===";

const string status_modifications_not_staged_header = "=== Modifications Not Staged For Commit ===";

const string msg_status_deleted = " (deleted)";

const string msg_status_modified = " (modified)";

const string status_untracked_files_header = "=== Untracked Files ===";

string get_merge_commit_message(const Blob *given_branch, const Blob *current_branch)
{
    string message("Merged " + given_branch->name + " into " + current_branch->name + ".");
    return message;
}

void init(Blob *&current_branch, List *&branches, List *&staged_files, List *&tracked_files, Commit *&head_commit)
{
    // Initialize the linked lists: branches, staged_files, tracked_files.
    branches = list_new();
    staged_files = list_new();
    tracked_files = list_new();

    Commit *initial_commit = new Commit; // create the initial commit
    std::string time = get_time_string();
    initial_commit->message = msg_initial_commit;                   // with msg "initial commit"
    initial_commit->time = time;                                    // set the time string
    initial_commit->commit_id = get_sha1(msg_initial_commit, time); // and compute the hash
    initial_commit->tracked_files = list_new();                     // This commit tracks no files (initialize commit->tracked_files as well)
    initial_commit->parent = nullptr;                               // and has no parents
    initial_commit->second_parent = nullptr;                        // and has no parents

    Blob *newBranch = new Blob;         // Create a branch
    newBranch->name = "master";         // called master
    current_branch = newBranch;         // and set it as the current branch.
    newBranch->commit = initial_commit; // add the initial commit to the branch
    head_commit = initial_commit;       // Set the head commit of the repository
    list_push_back(branches, newBranch);
}

bool add(const string &filename, List *staged_files, List *tracked_files, const Commit *head_commit)
{
    /*the wrapper function will check whether the file exists*/

    // save the content of the file to the currently tracked files of the repository.
    string hashValue = get_sha1(filename);
    list_put(tracked_files, filename, hashValue);

    // check whether the file is tracked in the head commit of the repository, with the same content as the current file
    bool alreadyTracked = list_find_name(head_commit->tracked_files, filename) == nullptr ? false : true;
    bool haveSameContent = false;
    if (alreadyTracked)
        haveSameContent = list_find_name(head_commit->tracked_files, filename)->ref == hashValue ? true : false;

    // If the file is tracked in the head commit of the repository, with the same content as the current file,
    // then remove the file from the staging area (if it is staged). Return false.
    if (alreadyTracked && haveSameContent)
    {
        // check whether this file is already staged
        bool alreadyStaged = list_find_name(staged_files, filename) == nullptr ? false : true;

        // if it is staged, then remove the file from the staging area
        if (alreadyStaged)
            list_remove(staged_files, filename);

        return false;
    }
    else // simply save the content of the file to the staging area as well. Return true.
    {
        list_put(staged_files, filename, hashValue);
        return true;
    }
}

bool commit(const string &message, Blob *current_branch, List *staged_files, List *tracked_files, Commit *&head_commit)
{
    /* Failure check: If there are no files in the staging area, and no files staged for removal,
     print No changes added to the commit. and return false.*/
    bool noFilesInStagingArea = list_size(staged_files) == 0 ? true : false;
    bool existFilesStagedForRemoval = false;
    if (list_size(head_commit->tracked_files) == 0) // if the head commit didn't track any files, it couldn't have tracked this file
    {
        existFilesStagedForRemoval = false;
    }
    else // this means the head commit did track some file
    {
        Blob *temp = head_commit->tracked_files->head->next; // set a temp ptr pointing at the 1st tracked file of the head commit of the repository
        while (temp != head_commit->tracked_files->head)     // go through every file tracked by the head commit
        {
            if (list_find_name(tracked_files, temp->name) == nullptr) // this means a file tracked by the head commit is not currently tracked by the repository
                existFilesStagedForRemoval = true;

            temp = temp->next;
        }
    }
    if (noFilesInStagingArea && !existFilesStagedForRemoval)
    {
        cout << msg_no_changes_added << endl;
        return false;
    }

    /*Create a new commit. Save the message, time and commit id.*/
    Commit *newCommit = new Commit;
    string time = get_time_string();
    string commit_id = get_sha1(message, time);
    newCommit->message = message;
    newCommit->time = time;
    newCommit->commit_id = commit_id;

    /*Take a snapshot of the repository by copying the tracked files of the repository to the tracked files of this commit.
    These files become the files that are tracked by this commit.*/
    newCommit->tracked_files = list_copy(tracked_files);

    /*Add this commit to the current branch and update the head commit of the repository.*/
    current_branch->commit = newCommit;
    newCommit->parent = head_commit;
    head_commit = newCommit;

    /*Clear the staging area and return true.*/
    list_clear(staged_files);
    return true;
}

bool remove(const string &filename, List *staged_files, List *tracked_files, const Commit *head_commit)
{
    /*check whether the file is tracked by the head commit of the repository, */
    bool trackedByHeadCommit = list_find_name(head_commit->tracked_files, filename) == nullptr ? false : true;
    if (trackedByHeadCommit)
    {
        list_remove(tracked_files, filename); // remove it from the current tracked files of the repository
        if (is_file_exist(filename))          // and remove the file from the current working directory (if it exists).
            restricted_delete(filename);
    }

    /*check whether the file was staged for Addition*/
    bool stagedForAddition = list_find_name(staged_files, filename);
    if (stagedForAddition)
    {
        list_remove(tracked_files, filename); // remove it from the tracked files of the repository
        list_remove(staged_files, filename);  // remove it from the staging area
    }

    /*If none of the above is satisfied, print No reason to remove the file. and return false*/
    if (!trackedByHeadCommit && !stagedForAddition)
    {
        cout << msg_no_reason_remove << endl;
        return false;
    }

    /* otherwise, return true*/
    return true;
}

void log(const Commit *head_commit)
{
    const Commit *temp = head_commit; // create a "temp" pointing to the head commit
    while (temp->parent != nullptr)
    {
        cout << "===" << endl;
        commit_print(temp);
        cout << endl
             << endl;
        temp = temp->parent;
    }
    // at the moment leaving the loop, temp points at the initial commit, print the initial commit as well
    cout << "===" << endl;
    commit_print(temp);
    cout << endl
         << endl;
}

void status(const Blob *current_branch, const List *branches, const List *staged_files, const List *tracked_files,
            const List *cwd_files, const Commit *head_commit)
{
    Blob *temp = nullptr;

    /* Part 1, branches */
    if (1)
    {
        /* display the names of all branches, mark the current branch with * */
        temp = branches->head->next; // temp points at the first branch in branches
        cout << status_branches_header << endl;
        while (temp != branches->head)
        {
            if (temp == current_branch)
                cout << '*';
            cout << temp->name << endl;
            temp = temp->next;
        }
    }

    cout << endl;

    /* Part 2, staged files */
    if (1)
    {
        cout << status_staged_files_header << endl;
        /*Display the filenames of all files that are staged for addition.*/
        if (list_size(staged_files) == 0)
        {
            /*do nothing*/
        }
        else
        {
            temp = staged_files->head->next; // temp points at the first staged file in staged_files

            while (temp != staged_files->head)
            {
                cout << temp->name << endl;
                temp = temp->next;
            }
        }

        cout << endl;
    }

    /* Part 3, removed files */
    if (1)
    {
        /*Display the filenames of all files that are staged for removal.*/
        // go through each file that is tracked by the head commit, and see if it is tracked by the repository.
        // if it is tracked by the head commit and not tracked by the repository, then it is a file "staged for removal", print it.
        cout << status_removed_files_header << endl;
        if (list_size(head_commit->tracked_files) == 0) // no files tracked by head commit, so no files staged for removal
        {
            /* dont't print anything*/
        }
        else // the head commit did track some files
        {
            temp = head_commit->tracked_files->head->next; // "temp" points at the 1st file tracked by the head commit
            while (temp != head_commit->tracked_files->head)
            {
                if (list_find_name(tracked_files, temp->name) == nullptr) // this file isn't tracked by the repository
                {
                    // print the name of this file
                    cout << temp->name << endl;
                }
                temp = temp->next;
            }
        }
    }

    cout << endl;

    /* Part 4, Modifications not staged for commit */
    if (1)
    {
        // create a new list storing all files to display in ascending lexicographic order
        List *files_to_display = list_new();

        /* Situation 1: Unstaged files that are tracked in the head commit of the repository,
        but the content recorded in the commit is different with the content in the current working directory*/
        if (1)
        {
            if (list_size(head_commit->tracked_files) == 0) // no files tracked by head commit, then nothing to display for this situation
            {
                /* dont't do anything*/
            }
            else // the head commit did track some files, go through every file tracked by the head commit
            {
                // go through every file tracked by the head commit and see whether it's unstaged
                temp = head_commit->tracked_files->head->next; // "temp" points at the 1st file tracked by the head commit
                while (temp != head_commit->tracked_files->head)
                {
                    if (list_find_name(staged_files, temp->name) == nullptr) // this file is unstaged
                    {
                        if (is_file_exist(temp->name))
                        {
                            // check whether the content recorded in the commit is different with the content in the current working directory
                            if (temp->ref != get_sha1(temp->name)) // if they are different, add it to files_to_display
                            {
                                list_put(files_to_display, temp->name, "1");
                            }
                        }
                    }
                    temp = temp->next;
                }
            }
        }

        /* Situation 2: Files that were staged for addition,
        but the content recorded in the staging area is different with the content in CWD.*/
        if (1)
        {
            // go through every file staged for addition and see whether the content recorded in the staging area is different with the content in CWD.
            temp = staged_files->head->next; // "temp" points at the 1st file staged for addition
            while (temp != staged_files->head)
            {
                if (is_file_exist(temp->name))
                {
                    if (temp->ref != get_sha1(temp->name))
                    {
                        list_put(files_to_display, temp->name, "2");
                    }
                }
                temp = temp->next;
            }
        }

        /*Situation 3: Files staged for addition but deleted in CWD.*/
        if (1)
        {
            // go through every file staged for addition and check whether that file exists in CWD
            temp = staged_files->head->next; // "temp" points at the 1st file staged for addition
            while (temp != staged_files->head)
            {
                if (!is_file_exist(temp->name))
                {
                    list_put(files_to_display, temp->name, "3");
                }
                temp = temp->next;
            }
        }

        /*Situation 4: Files not staged for removal but tracked in the head commit of the repository and deleted in CWD.*/
        if (1)
        {
            // this situation is equivalent to files that are: "traked by head commit" && "tracked by the repo" && "deleted in CWD"

            // go through every file "tracked by head commit" and check whether it's "traked by the repo" && "deleted in CWD"
            temp = head_commit->tracked_files->head->next; // temp points at the 1st file tracked by head commit
            while (temp != head_commit->tracked_files->head)
            {
                if (list_find_name(tracked_files, temp->name) != nullptr && !is_file_exist(temp->name))
                {
                    list_put(files_to_display, temp->name, "4");
                }
                temp = temp->next;
            }
        }

        // go through the list of files to display and print them
        cout << status_modifications_not_staged_header << endl;
        temp = files_to_display->head->next; // temp points at the 1st file to display
        while (temp != files_to_display->head)
        {
            // print the name of this file
            cout << temp->name;
            // append (modified) or (deleted) depending in situation 1-4
            if (temp->ref == "1" || temp->ref == "2")
            {
                cout << msg_status_modified << endl;
            }
            else if (temp->ref == "3" || temp->ref == "4")
            {
                cout << msg_status_deleted << endl;
            }
            temp = temp->next;
        }

        // remember to delete the temporary list
        list_delete(files_to_display);
    }

    cout << endl;

    /* Part 5, Untracked files */
    if (1)
    {
        cout << status_untracked_files_header << endl;
        // Files exist in CWD but not currently tracked by the repository
        if (list_size(cwd_files) == 0) // there is no file in CWD
        {
            /* don't do anything */
        }
        else // there exist files in the CWD
        {
            temp = cwd_files->head->next; // temp points at the 1st file in the CWD
            while (temp != cwd_files->head)
            {
                if (list_find_name(tracked_files, temp->name) == nullptr)
                {
                    // print the name of this file
                    cout << temp->name << endl;
                }
                temp = temp->next;
            }
        }
    }
}

bool checkout(const string &filename, Commit *commit)
{
    /* Faliure check */
    if (commit == nullptr)
    {
        cout << msg_commit_does_not_exist << endl;
        return false;
    }
    if (list_find_name(commit->tracked_files, filename) == nullptr)
    {
        cout << msg_file_does_not_exist << endl;
        return false;
    }

    write_file(filename, list_find_name(commit->tracked_files, filename)->ref);
    return true;
}

bool checkout(const string &branch_name, Blob *&current_branch, const List *branches, List *staged_files,
              List *tracked_files, const List *cwd_files, Commit *&head_commit)
{
    /* Failure check */
    /*If the given branch does not exist, print A branch with that name does not exist. and return false.*/
    if (list_find_name(branches, branch_name) == nullptr)
    {
        cout << msg_branch_does_not_exist << endl;
        return false;
    }
    /*If the given branch is the current branch, print No need to checkout the current branch. and return false.*/
    if (branch_name == current_branch->name)
    {
        cout << msg_checkout_current << endl;
        return false;
    }
    /*If there exists untracked files in the current working directory that would be overwritten*/
    Blob *temp = cwd_files->head->next; // go through all the files in cwd
    while (temp != cwd_files->head)
    {
        if (list_find_name(tracked_files, temp->name) == nullptr) // if it's untracked, check whether it will be overwritten
        {
            List *tracked_files_of_target_branch_head_commit = list_find_name(branches, branch_name)->commit->tracked_files;
            Blob *theFileInTargetBranch = list_find_name(tracked_files_of_target_branch_head_commit, temp->name);
            if (theFileInTargetBranch == nullptr)
            {
                // this means this file wasn't tracked by the head commit of the target branch, so will not overwrite
            }
            else // this means this file was tracked by the head commit of the target branch, check whether content is same
            {
                if (get_sha1(temp->name) != theFileInTargetBranch->ref) // content is different, will overwrite
                    cout << msg_untracked_file << endl;
                return false;
            }
        }
        temp = temp->next;
    }

    /*Take all files in the head commit of that branch and write the content of them to the current working directory.*/
    temp = list_find_name(branches, branch_name)->commit->tracked_files->head->next;
    while (temp != list_find_name(branches, branch_name)->commit->tracked_files->head) // go through all files tracked by the head commit of that bracnch
    {
        write_file(temp->name, temp->ref);
        temp = temp->next;
    }

    /*Any files that are tracked in the head commit of the repository but not the head commit of the given branch are deleted.*/
    temp = head_commit->tracked_files->head->next;
    while (temp != head_commit->tracked_files->head) // go through every file that are tracked in the head commit of the repository
    {
        if (list_find_name(list_find_name(branches, branch_name)->commit->tracked_files, temp->name) == nullptr) // not tracked by head commit of the given branch
        {
            if (is_file_exist(temp->name))
            {
                restricted_delete(temp->name);
            }
        }
        temp = temp->next;
    }

    /*Set the currently tracked files of the repository to those that are tracked by the head commit of the given branch.*/
    list_replace(tracked_files, list_find_name(branches, branch_name)->commit->tracked_files);

    /* clear the staging area */
    list_clear(staged_files);

    /*The given branch becomes the current branch*/
    current_branch = list_find_name(branches, branch_name);

    /*update the head commit of the repository.*/
    head_commit = list_find_name(branches, branch_name)->commit;

    return true;
}

bool reset(Commit *commit, Blob *current_branch, List *staged_files, List *tracked_files, const List *cwd_files,
           Commit *&head_commit)
{
    /*Faliure check*/
    /* If commit is nullptr, then the wrapper cannot find the commit with the commit id.
    Print No commit with that id exists. and return false.*/
    if (commit == nullptr)
    {
        cout << msg_commit_does_not_exist << endl;
        return false;
    }
    /*If there exists untracked files in the current working directory that would be overwritten*/
    Blob *temp = cwd_files->head->next; // go through all files in cwd
    while (temp != cwd_files->head)
    {
        if (list_find_name(tracked_files, temp->name) == nullptr) // if it's untracked, check whether it will be overwritten
        {
            List *tracked_files_of_given_commit = commit->tracked_files;
            Blob *theFileInGivenCommit = list_find_name(tracked_files_of_given_commit, temp->name);
            if (theFileInGivenCommit == nullptr)
            {
                // this means this file is not tracked in the given commit, so will not overwrite
            }
            else // this means this file is tracked by the given commit, check whether content is same
            {
                if (get_sha1(temp->name) != theFileInGivenCommit->ref)
                {
                    cout << msg_untracked_file << endl;
                    return false;
                }
            }
        }
        temp = temp->next;
    }

    /*Take all files in the given commit and write the content of them to the current working directory.*/
    temp = commit->tracked_files->head->next;
    while (temp != commit->tracked_files->head)
    {
        write_file(temp->name, temp->ref);
        temp = temp->next;
    }

    /*Any files that are tracked in the head commit of the repository but not by the given commit are deleted.*/
    temp = head_commit->tracked_files->head->next;
    while (temp != head_commit->tracked_files->head)
    {
        if (list_find_name(commit->tracked_files, temp->name) == nullptr)
        {
            if (is_file_exist(temp->name))
            {
                restricted_delete(temp->name);
            }
        }
        temp = temp->next;
    }

    /*Set the currently tracked files of the repository to those that are tracked by the given commit*/
    list_replace(tracked_files, commit->tracked_files);

    /* clear the staging area */
    list_clear(staged_files);

    /*The given commit becomes the head commit of the current branch.*/
    current_branch->commit = commit;

    /* Also update the head commit of the repository.*/
    head_commit = commit;

    return true;
}

Blob *branch(const string &branch_name, List *branches, Commit *head_commit)
{
    /*Faliure check*/
    if (list_find_name(branches, branch_name) != nullptr)
    {
        cout << msg_branch_exists << endl;
        return nullptr;
    }

    /*create the new branch, The head commit of the repository becomes the head commit of the new branch.*/
    list_put(branches, branch_name, head_commit);

    return list_find_name(branches, branch_name);
}

bool remove_branch(const string &branch_name, Blob *current_branch, List *branches)
{
    /*Failure check*/
    if (list_find_name(branches, branch_name) == nullptr)
    {
        cout << msg_branch_does_not_exist << endl;
        return false;
    }
    if (list_find_name(branches, branch_name) == current_branch)
    {
        cout << msg_remove_current << endl;
        return false;
    }

    /*Delete the branch from the repository. Do not delete any commits.*/
    list_remove(branches, branch_name);

    return true;
}

bool merge(const string &branch_name, Blob *&current_branch, List *branches, List *staged_files, List *tracked_files,
           const List *cwd_files, Commit *&head_commit)
{
    /* Failure check */
    /*If the given branch does not exist, print A branch with that name does not exist., and return false*/
    if (list_find_name(branches, branch_name) == nullptr)
    {
        cout << msg_branch_does_not_exist << endl;
        return false;
    }
    /*If trying to merge the current branch, print Cannot merge a branch with itself. and return false*/
    if (branch_name == current_branch->name)
    {
        cout << msg_merge_current << endl;
        return false;
    }
    /*If there exists uncommitted changes, print You have uncommitted changes. and return false.*/
    // Uncommitted changes refer to those that appear in status “Staged Files” and “Removed Files”.
    if (list_size(staged_files) != 0)
    {
        cout << msg_exists_uncommitted_changes << endl;
        return false;
    }
    // go through each file that is tracked by the head commit, and see if it is tracked by the repository.
    // if it is tracked by the head commit and not tracked by the repository, then it is a file "staged for removal"
    if (list_size(head_commit->tracked_files) == 0) // no files tracked by head commit, so no files staged for removal
    {
        /* dont't do anything*/
    }
    else // the head commit did track some files
    {
        Blob *temp = head_commit->tracked_files->head->next; // "temp" points at the 1st file tracked by the head commit
        while (temp != head_commit->tracked_files->head)
        {
            if (list_find_name(tracked_files, temp->name) == nullptr) // this file isn't tracked by the repository
            {
                cout << msg_exists_uncommitted_changes << endl;
                return false;
            }
            temp = temp->next;
        }
    }

    /*Otherwise, proceed to compute the split point of the current branch and the given branch. */
    Blob *givenBranch = list_find_name(branches, branch_name);
    Commit *splitPoint = get_lca(current_branch->commit, givenBranch->commit);

    /*If the split point is the head commit of the given branch,
    then all changes in the given branch exist in the current branch (the current branch is ahead of the given branch).
    So there is nothing to be done in the current branch.
    Simply print Given branch is an ancestor of the current branch. and return true*/
    if (splitPoint == givenBranch->commit)
    {
        cout << msg_given_is_ancestor_of_current << endl;
        return true;
    }

    /*Traverse cwd_files, if there exists a file that is not tracked in the head commit of the current branch
    but tracked in the head commit of the given branch,
    print There is an untracked file in the way; delete it, or add and commit it first. and return false.*/
    Blob *temp = cwd_files->head->next;
    while (temp != cwd_files->head) // Traverse cwd_files
    {
        if (list_find_name(current_branch->commit->tracked_files, temp->name) == nullptr) // a file that is not tracked in the head commit of the current branch
        {
            if (list_find_name(givenBranch->commit->tracked_files, temp->name) != nullptr) // but tracked in the head commit of the given branch
            {
                cout << msg_untracked_file << endl;
                return false;
            }
        }

        temp = temp->next;
    }

    /*If the split point is the head commit of the current branch,
    then all changes in the current branch exist in the given branch (the given branch is ahead of the current branch).
    Simply set the state of the repository to the head commit of the given branch (using one command above).
    If it succeeded, print Current branch fast-forwarded. and return true. If it failed, return false.*/
    if (splitPoint == current_branch->commit)
    {
        bool success;
        success = reset(givenBranch->commit, current_branch, staged_files, tracked_files, cwd_files, head_commit);
        if (success)
        {
            cout << msg_fast_forward << endl;
            return true;
        }
        else
        {
            return false;
        }
    }

    /*Otherwise, the split point is neither the head commit of the current branch or the head commit of the given branch.
    Their history has diverged, like the above example. We need to incorporate the latest changes from both branches.*/

    /*Otherwise, proceed to merge the two branches with rules below.
    A general idea is to incorporate the latest changes from both branches.*/

    /*1. Any files that have been modified in the given branch
    but not modified in the current branch since the split point
    should be changed to their versions in the given branch.*/

    // go through everyfile tracked by the head commit in the current branch
    temp = current_branch->commit->tracked_files->head->next; // temp points at 1st file of the head commit of current branch
    while (temp != current_branch->commit->tracked_files->head)
    {
        string versionInHeadOfCurrentBranch = temp->ref;
        Blob *theFileAtSplitPoint = list_find_name(splitPoint->tracked_files, temp->name);
        Blob *theFileInGivenBranch = list_find_name(givenBranch->commit->tracked_files, temp->name);
        string versionInSplitPoint = theFileAtSplitPoint == nullptr ? "null" : theFileAtSplitPoint->ref;
        string versionInGivenBranch = theFileInGivenBranch == nullptr ? "null" : theFileInGivenBranch->ref;
        if (theFileAtSplitPoint != nullptr && theFileInGivenBranch != nullptr) // if the file is tracked by the splitpoint commit and also the head commit of given branch
        {
            if (versionInHeadOfCurrentBranch == versionInSplitPoint) // if the file haven't been modified since the split point in the current branch
            {
                // check whether the same file has been modified in the given branch
                if (versionInHeadOfCurrentBranch != versionInGivenBranch)
                {
                    /*this means the same file has been modified in the given branch, need to change the version in the current branch
                    into the version in the given branch*/
                    checkout(temp->name, givenBranch->commit);                 // checkout the file
                    add(temp->name, staged_files, tracked_files, head_commit); // stage the files for addition.
                    stage_content(temp->name);                                 // In addition, you need to call stage_content(filename) explicitly to modify the index in the .gitlite directory.
                }
            }
        }
        temp = temp->next;
    }

    /*2.Any files that have been modified in the current branch
    but not modified in the given branch since the split point should remain unchanged.*/

    /*3.Any files that have been modified in both the current branch and the given branch in the same way
    (both modified with same content or both removed), should remain unchanged.*/

    /*4.Any files that were not present at the split point
    and are present only in the current branch should remained unchanged.*/

    /*5.Any files that were not present at the split point
    and are present only in the given branch should be added with their versions in the given branch.*/

    // go through all files tracked by the head commit of the given branch and check whether they exist at the split point
    temp = givenBranch->commit->tracked_files->head->next;
    while (temp != givenBranch->commit->tracked_files->head)
    {
        if (list_find_name(splitPoint->tracked_files, temp->name) == nullptr) // the file was not presesnt at the split point
        {
            checkout(temp->name, givenBranch->commit);                 // checkout the file
            add(temp->name, staged_files, tracked_files, head_commit); // stage the files for addition.
            stage_content(temp->name);                                 // In addition, you need to call stage_content(filename) explicitly to modify the index in the .gitlite directory.
        }
        temp = temp->next;
    }

    /*6.Any files present at the split point, unmodified in the current branch, and absent in the given branch
    should be staged for removal.*/

    // go through everyfile tracked by the head commit in the current branch
    temp = current_branch->commit->tracked_files->head->next; // temp points at 1st file of the head commit of current branch
    while (temp != current_branch->commit->tracked_files->head)
    {
        Blob *theFileAtSplitPoint = list_find_name(splitPoint->tracked_files, temp->name);
        Blob *theFileInGivenBranch = list_find_name(givenBranch->commit->tracked_files, temp->name);
        string versionInSplitPoint = theFileAtSplitPoint == nullptr ? "null" : theFileAtSplitPoint->ref;
        string versionInHeadOfCurrentBranch = temp->ref;
        if (theFileAtSplitPoint != nullptr) // if the file is present at the split point
        {
            if (versionInHeadOfCurrentBranch == versionInSplitPoint) // if the file haven't been modified since the split point in the current branch
            {
                if (theFileInGivenBranch == nullptr) // if the file is absent in the given branch
                {
                    /*it needs to be staged for removal*/

                    /*PS: If the file is tracked by the head commit of the repository,
                    then remove it from the currently tracked files of the repository and remove the file from the current working directory (if it exists).
                    The file is staged for removal.*/

                    list_remove(tracked_files, temp->name);
                    if (is_file_exist(temp->name))
                        restricted_delete(temp->name);
                }
            }
        }
        temp = temp->next;
    }

    /*7.Any files present at the split point, unmodified in the given branch, and absent in the current branch
    should remain absent.*/

    /*8.Any files modified in different ways in the current branch and the given branch are in conflict.*/
    List *files_in_conflict = list_new();

    /* first find all files that are in conflict and store them in a list, this include:
        a.It is changed in both branches with different content.
        b.It is changed in one branch but deleted in another branch.
        c.It was absent at the split point but present in both branches with different content.*/

    /*situation a*/
    // go through everyfile tracked by the head commit in the current branch
    temp = current_branch->commit->tracked_files->head->next; // temp points at 1st file of the head commit of current branch
    while (temp != current_branch->commit->tracked_files->head)
    {
        if (list_find_name(splitPoint->tracked_files, temp->name) != nullptr &&        // exist at split point
            list_find_name(givenBranch->commit->tracked_files, temp->name) != nullptr) // exist in given branch
        {
            // a file existing in all current_branch, given_branch, splitpoint
            // the file is modified in both branches
            if (temp->ref != list_find_name(splitPoint->tracked_files, temp->name)->ref &&
                list_find_name(givenBranch->commit->tracked_files, temp->name)->ref != list_find_name(splitPoint->tracked_files, temp->name)->ref)
            {
                if (temp->ref != list_find_name(givenBranch->commit->tracked_files, temp->name)->ref)
                {

                    // this means the file is changed in both branches with different content
                    list_put(files_in_conflict, temp->name, list_find_name(givenBranch->commit->tracked_files, temp->name)->ref);
                }
            }
        }
        temp = temp->next;
    }

    /*situation b*/
    // go through everyfile tracked by the split point commit
    temp = splitPoint->tracked_files->head->next;
    while (temp != splitPoint->tracked_files->head)
    {
        // if exist in current branch but deleted in given branch
        if (list_find_name(givenBranch->commit->tracked_files, temp->name) == nullptr &&
            list_find_name(current_branch->commit->tracked_files, temp->name) != nullptr)
        {
            // if changed in current branch
            if (temp->ref != list_find_name(current_branch->commit->tracked_files, temp->name)->ref)
            {
                list_put(files_in_conflict, temp->name, string());
            }
        }
        // or if exist in given branch bur deleted in current branch
        else if (list_find_name(givenBranch->commit->tracked_files, temp->name) != nullptr &&
                 list_find_name(current_branch->commit->tracked_files, temp->name) == nullptr)
        {
            // if changed in given branch
            if (temp->ref != list_find_name(givenBranch->commit->tracked_files, temp->name)->ref)
            {
                list_put(files_in_conflict, temp->name, list_find_name(givenBranch->commit->tracked_files, temp->name)->ref);
            }
        }
        temp = temp->next;
    }

    /*situation c*/
    // go through everyfile tracked by the head commit in the current branch
    temp = current_branch->commit->tracked_files->head->next; // temp points at 1st file of the head commit of current branch
    while (temp != current_branch->commit->tracked_files->head)
    {
        if (list_find_name(splitPoint->tracked_files, temp->name) == nullptr &&        // absent at split point
            list_find_name(givenBranch->commit->tracked_files, temp->name) != nullptr) // exist in given branch
        {
            if (temp->ref != list_find_name(givenBranch->commit->tracked_files, temp->name)->ref)
            {
                // this means the file is newly created in both branches with different content
                list_put(files_in_conflict, temp->name, list_find_name(givenBranch->commit->tracked_files, temp->name)->ref);
            }
        }
        temp = temp->next;
    }

    // Replace the content of these files in the current working directory by the conflict resolution marker:
    // go through all of these files
    temp = files_in_conflict->head->next;
    while (temp != files_in_conflict->head)
    {
        /* code */
        add_conflict_marker(temp->name, temp->ref);
        add(temp->name, staged_files, tracked_files, head_commit);
        stage_content(temp->name);
        temp = temp->next;
    }

    if (list_size(files_in_conflict) != 0)
        cout << msg_encountered_merge_conflict << endl;

    // remember to delete the temporary list
    list_delete(files_in_conflict);

    /*After processing the files, create a merge commit with message Merged [given branch name] into [current branch name].*/
    string commitMsg = get_merge_commit_message(givenBranch, current_branch);
    commit(commitMsg, current_branch, staged_files, tracked_files, head_commit);
    head_commit->second_parent = givenBranch->commit;

    return true;
}
