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

    //check whether the file is tracked in the head commit of the repository, with the same content as the current file
    bool alreadyTracked = list_find_name(head_commit->tracked_files, filename) == nullptr ? false : true;
    bool haveSameContent = false;
    if (alreadyTracked)
        haveSameContent = list_find_name(head_commit->tracked_files, filename)->ref == hashValue ? true : false;

    //If the file is tracked in the head commit of the repository, with the same content as the current file,
    //then remove the file from the staging area (if it is staged). Return false.
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
        stage_content(filename);
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
    if (list_size(head_commit->tracked_files) == 0) //if the head commit didn't track any files, it couldn't have tracked this file
    {
        existFilesStagedForRemoval = false;
    }
    else // this means the head commit did track some file
    {
        Blob *temp = head_commit->tracked_files->head->next; //set a temp ptr pointing at the 1st tracked file of the head commit of the repository
        while (temp != head_commit->tracked_files->head)     // go through every file tracked by the head commit
        {
            if (list_find_name(tracked_files, temp->name) == nullptr) //this means a file tracked by the head commit is not currently tracked by the repository
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
        if (is_file_exist(filename))          //and remove the file from the current working directory (if it exists).
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
                    //go through every file tracked by the head commit and see whether it's unstaged
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
                if (list_size(staged_files) == 0) // no file is staged for addition
                {
                    /* don't do anything */
                }
                else // there are some files staged for addition
                {
                    //go through every file staged for addition and see whether the content recorded in the staging area is different with the content in CWD.
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
            }

            /*Situation 3: Files staged for addition but deleted in CWD.*/
            if (1)
            {
                if (list_size(staged_files) == 0) // no file is staged for addition
                {
                    /* don't do anything */
                }
                else
                {
                    //go through every file staged for addition and check whether that file exists in CWD
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
            while (temp->next != files_to_display->head)
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

    write_file(filename, commit->commit_id);
    return true;
}

bool checkout(const string &branch_name, Blob *&current_branch, const List *branches, List *staged_files,
              List *tracked_files, const List *cwd_files, Commit *&head_commit)
{
    return false;
}

bool reset(Commit *commit, Blob *current_branch, List *staged_files, List *tracked_files, const List *cwd_files,
           Commit *&head_commit)
{
    return false;
}

Blob *branch(const string &branch_name, List *branches, Commit *head_commit)
{
    return nullptr;
}

bool remove_branch(const string &branch_name, Blob *current_branch, List *branches)
{
    return false;
}

bool merge(const string &branch_name, Blob *&current_branch, List *branches, List *staged_files, List *tracked_files,
           const List *cwd_files, Commit *&head_commit)
{
    return false;
}
