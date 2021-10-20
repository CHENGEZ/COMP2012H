#include "Commit.h"
#include "Utils.h"

using namespace std;

// Part 1: Linked List Operations

List *list_new()
{
    List *newList = new List;
    Blob *head = new Blob;
    head->prev = head;
    head->next = head;

    newList->head = head;
    return newList;
}

void list_push_back(List *list, Blob *blob)
{
    Blob *temp = list->head;         // initially, this "temp" points at the first node
    while (temp->next != list->head) // go through the list to find the last node
    {
        temp = temp->next;
    }
    // now "temp" points at the last node:
    temp->next = blob;
    blob->prev = temp;
    blob->next = list->head;
    list->head->prev = blob;
}

Blob *list_find_name(const List *list, const string &name)
{
    Blob *temp = list->head; // initially, this "temp" points at the first node
    while (temp->name != name)
    {
        temp = temp->next;

        if (temp == list->head) // if after temp becomes temp->next, temp points to head, this means it has gone through the whole list
        {
            return nullptr;
        }
    }
    return temp;
}

Blob *list_put(List *list, const string &name, const string &ref)
{
    Blob *temp = list_find_name(list, name);

    if (temp != nullptr) // this means a blob with the same name already exists in the linked list
    {
        temp->ref = ref;
        return temp;
    }
    else // this means no blobs with the same name exists in the linked list
    {
        temp = list->head->next; // point it to the first non-sentinal node
        /* creat the new blob with given content */
        Blob *newBlob = new Blob;
        newBlob->name = name;
        newBlob->ref = ref;
        /* insert it to the correct position */
        while (temp->name < name)
        {
            if (temp->next == list->head) // this means the name of the last node is still smaller than the new one
            {
                list_push_back(list, newBlob);
                return newBlob;
            }
            temp = temp->next;
        }
        // at the moment exiting the loop, temp points at the node before which we will insert the new Node
        Blob *temp2 = temp; // another ptr temp2 pointing to the node before which we will insert the new node
        temp = temp->prev;  // temp points to the node after which we will insert the new node

        temp->next = newBlob;
        newBlob->next = temp2;
        newBlob->prev = temp;
        temp2->prev = newBlob;
        return newBlob;
    }
}

Blob *list_put(List *list, const string &name, Commit *commit)
{
    Blob *temp = list_find_name(list, name);

    if (temp != nullptr) // this means a blob with the same name already exists in the linked list
    {
        temp->commit = commit;
        return temp;
    }
    else // this means no blobs with the same name exists in the linked list
    {
        temp = list->head->next; // point it to the first non-sentinal node
        /* creat the new blob with given content */
        Blob *newBlob = new Blob;
        newBlob->name = name;
        newBlob->commit = commit;
        /* insert it to the correct position */
        while (temp->name < name)
        {
            if (temp->next == list->head) // this means the name of the last node is still smaller than the new one
            {
                list_push_back(list, newBlob);
                return newBlob;
            }
            temp = temp->next;
        }
        // at the moment exiting the loop, temp points at the node before which we will insert the new Node
        Blob *temp2 = temp; // another ptr temp2 pointing to the node before which we will insert the new node
        temp = temp->prev;  // temp points to the node after which we will insert the new node

        temp->next = newBlob;
        newBlob->next = temp2;
        newBlob->prev = temp;
        temp2->prev = newBlob;
        return newBlob;
    }
}

bool list_remove(List *list, const string &target)
{
    Blob *temp = list_find_name(list, target);

    if (temp == nullptr)
        return false;
    else
    {
        Blob *left = temp->prev;
        Blob *right = temp->next;
        left->next = right;
        right->prev = left;
        delete temp;
        return true;
    }
}

int list_size(const List *list)
{
    int numOfBlobs = 0;
    Blob *temp = list->head; // initially, this "temp" points at the first node

    while (temp->next != list->head)
    {
        numOfBlobs++;
        temp = temp->next;
    }

    return numOfBlobs;
}

void list_clear(List *list)
{
    if (list_size(list) == 0)
        return;
    Blob *temp = list->head->next; // initially, this "temp" points at the second node (the first is sentinal)
    while (temp->next != list->head)
    {
        Blob *temp2 = temp;
        temp = temp->next;
        delete temp2;
    }
    // at the moment exiting the loop, temp should point to the last node in the list, so delete the last one as well
    delete temp;
    temp = nullptr;
    list->head->next = list->head;
    list->head->prev = list->head;
}

void list_delete(List *list)
{
    list_clear(list); // Only the sentinal node is left after this
    delete list->head;
    list->head = nullptr;
    delete list;
    list = nullptr;
}

void list_replace(List *list, const List *another)
{
    list_clear(list); // Only the sentinal node is left after this
    if (list_size(another) == 0)
        return;
    Blob *temp = another->head->next; // initially, this "temp" points at the second node of the "another" linked list
    while (temp->next != another->head)
    {
        Blob *deepCopy = new Blob;
        *deepCopy = *temp;
        list_push_back(list, deepCopy);
        temp = temp->next;
    }
    // at the moment exiting the loop, temp should be pointing at the last node in "another"
    Blob *deepCopy = new Blob;
    *deepCopy = *temp;
    list_push_back(list, deepCopy);
}

List *list_copy(const List *list)
{
    List *newList = list_new();
    if (list_size(list) == 0)
        return newList;

    Blob *temp = list->head->next; // initially, this "temp" points at the second node of the linked list to be copied
    while (temp->next != list->head)
    {
        Blob *deepCopy = new Blob;
        *deepCopy = *temp;
        list_push_back(newList, deepCopy);
        temp = temp->next;
    }
    // at the moment exiting the loop, temp should be pointing at the last node of the linked list to be copied
    Blob *deepCopy = new Blob;
    *deepCopy = *temp;
    list_push_back(newList, deepCopy);

    return newList;
}

// Part 2: Gitlite Commands

// Print out the commit info. Used in log.
void commit_print(const Commit *commit)
{
    cout << "commit " << commit->commit_id << endl;

    if (commit->second_parent != nullptr)
    {
        cout << "Merge: " << commit->parent->commit_id.substr(0, 7)
             << " " << commit->second_parent->commit_id.substr(0, 7) << endl;
    }

    cout << "Date: " << commit->time << endl
         << commit->message;
}

/* find latest ancestor */
void find_ancestor_commits(List *&reachable_commits_for_this_offspring, Commit *offspring)
{
    if (offspring == nullptr)
        return;

    list_put(reachable_commits_for_this_offspring, offspring->commit_id, offspring);

    find_ancestor_commits(reachable_commits_for_this_offspring, offspring->parent);
    find_ancestor_commits(reachable_commits_for_this_offspring, offspring->second_parent);
}

Commit *get_lca(Commit *c1, Commit *c2)
{
    List *reachable_commits_of_c1 = list_new();
    List *reachable_commits_of_c2 = list_new();
    List *common_reachable_commits = list_new();
    List *reachable_commits_of_the_other_commit = list_new();

    find_ancestor_commits(reachable_commits_of_c1, c1); // after this function call, all reachable commits of c1 should be stored in the list reachable_commits_of_c1
    find_ancestor_commits(reachable_commits_of_c2, c2); // after this function call, all reachable commits of c2 should be stored in the list reachable_commits_of_c2

    // go through the two lists of reachable commits to find all common ancestors of c1 and c2
    Blob *temp1 = reachable_commits_of_c1->head->next;
    Blob *temp2 = reachable_commits_of_c2->head->next;

    while (temp1 != reachable_commits_of_c1->head)
    {
        temp2 = reachable_commits_of_c2->head->next;

        while (temp2 != reachable_commits_of_c2->head)
        {
            if (temp2->name == temp1->name)
            {
                list_put(common_reachable_commits, temp1->name, temp1->commit);
            }
            temp2 = temp2->next;
        }

        temp1 = temp1->next;
    }
    // after exiting this loop, all common ancestors of c1 and c2 should be stored in the list common_reachable_commits
    // now we need to determine which one is the latest

    // cout << "the size of reachable commits of c1 is " << list_size(reachable_commits_of_c1) << endl;
    // cout << "the size of reachable commits of c2 is " << list_size(reachable_commits_of_c2) << endl;
    // cout << "the size of common reachable commits of c1 and c2 is " << list_size(common_reachable_commits) << endl;

    Commit *returnLCA = nullptr;
    Blob *thisCommonAncestor = common_reachable_commits->head->next;
    // go through all the common ancestors, and find ONE that is NOT reachable by any other common_reachable_commit except itself
    while (thisCommonAncestor != common_reachable_commits->head)
    {
        // cout << "entered outerloop" << endl;
        Blob *anotherCommonAncestor = thisCommonAncestor->next;
        bool reachableByAnother = false;
        while (anotherCommonAncestor != thisCommonAncestor)
        {
            if (anotherCommonAncestor == common_reachable_commits->head)
            {
                anotherCommonAncestor = anotherCommonAncestor->next;
                continue;
            }
            list_clear(reachable_commits_of_the_other_commit);
            find_ancestor_commits(reachable_commits_of_the_other_commit, anotherCommonAncestor->commit);
            if (list_find_name(reachable_commits_of_the_other_commit, thisCommonAncestor->name) != nullptr)
            {
                // this means for "this common ancestor", it is reachable by one of the others
                reachableByAnother = true;
                break;
            }
            anotherCommonAncestor = anotherCommonAncestor->next;
        }

        if (!reachableByAnother)
        {
            returnLCA = thisCommonAncestor->commit;
            break;
        }

        thisCommonAncestor = thisCommonAncestor->next;
    }

    list_delete(reachable_commits_of_c1);
    list_delete(reachable_commits_of_c2);
    list_delete(common_reachable_commits);
    list_delete(reachable_commits_of_the_other_commit);

    return returnLCA;
}

/*
Commit *get_lca(Commit *c1, Commit *c2)
{
    Commit *temp1 = c1;
    Commit *temp2 = c2;
    while (temp1 != nullptr) // when one's becomes nullptr, it means it has reached the head commit previously
    {
        while (temp2 != nullptr)
        {
            if (temp2 == temp1)
                return temp2;
            temp2 = temp2->parent;
        }
        temp2 = c2;
        temp1 = temp1->parent;
    }

    return nullptr;
}
*/