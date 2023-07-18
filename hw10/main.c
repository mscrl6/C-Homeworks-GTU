#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// all structs
typedef struct Node {
    void* data;
    struct Node* next;
} Node;

// asset1
typedef struct {
    char type[20];
    int ivals[1];
    double svals[1];
} Asset1;

// asset2
typedef struct {
    char type[20];
    double svals[2];
    int ivals[2];
} Asset2;

// asset3
typedef struct {
    char type[20];
    char string1[50];
    char string2[50];
} Asset3;

// asset4
typedef struct {
    char type[20];
    double value1;
    float value2;
    double value3;
} Asset4;

// all functions
void fillLinkedList(Node** head);
void serializeLinkedList(Node* head);
void deserializeLinkedList(Node** head);
void freeLinkedList(Node* head);

// fill the linked list function
void fillLinkedList(Node** head) {
    int asset_count = 10+ rand() % 11; // generating a random number between 10-20 for number of assets
    Node* iter = NULL;
    int i;
    for(i = 0; i < asset_count; i++){

        Node* node = malloc(sizeof(Node)); // creating a new node in each loop
        int asset_type = rand() % 4 + 1; // generating a random asset type

        // if asset type is 1 
        if(asset_type==1){
            Asset1* asset = (Asset1*)malloc(sizeof(Asset1));
            strcpy(asset->type, "Asset1");
            asset->ivals[0] = rand();
            asset->svals[0] = rand() / (double)RAND_MAX;
            node->data = asset; // filling the node data with asset
        }

        // if asset type is 2
        else if(asset_type==2){
            Asset2* asset = (Asset2*)malloc(sizeof(Asset2));
            strcpy(asset->type, "Asset2");
            asset->ivals[0] = rand();
            asset->ivals[1] = rand();
            asset->svals[0] = rand() / (double)RAND_MAX;
            asset->svals[1] = rand() / (double)RAND_MAX;
            node->data = asset; // filling the node data with asset
        }    

        // if asset type is 3       
        else if(asset_type==3){
            Asset3* asset = (Asset3*)malloc(sizeof(Asset3));
            strcpy(asset->type, "Asset3");
            strcpy(asset->string1,"Type3String1");
            strcpy(asset->string2,"Type3String2");
            node->data = asset; // filling the node data with asset
        }  

        // if asset type is 4    
        else if(asset_type==4){
            Asset4* asset = (Asset4*)malloc(sizeof(Asset4));
            strcpy(asset->type, "Asset4");
            asset->value1 = rand() / (double)RAND_MAX;
            asset->value2 = rand() / (float)RAND_MAX;
            asset->value3 = rand() / (double)RAND_MAX;
            node->data = asset; // filling the node data with asset
        }   

        node->next = NULL; 
        if(*head == NULL) {
            *head = node;
            iter = node; 
        } 
        else {
            iter->next = node;
            iter = iter->next;
        }
    }          
}

// serialize function
void serializeLinkedList(Node* head) {
    FILE* fp;
    fp=fopen("linkedlist.bin", "wb"); // opening the file in writing mode
    if(fp==NULL){
        printf("Error!\n");
        exit(0);
    }

    Node* iter = head;
    while(iter != NULL) {
        char* type = ((Asset1*)iter->data)->type; /*getting the 'type' field from the current node's data.
                                                    it could be asset2, asset3 or asset4. it doesn't matter*/ 
        if(strcmp(type, "Asset1") == 0) {
            fwrite(iter->data, sizeof(Asset1), 1, fp);
        }
        else if(strcmp(type, "Asset2") == 0) {
            fwrite(iter->data, sizeof(Asset2), 1, fp);
        } 
        else if(strcmp(type, "Asset3") == 0) {
            fwrite(iter->data, sizeof(Asset3), 1, fp);
        } 
        else if(strcmp(type, "Asset4") == 0) {
            fwrite(iter->data, sizeof(Asset4), 1, fp);
        }
        iter = iter->next;
    }
    fclose(fp);
}

// deserialize function
void deserializeLinkedList(Node** head) {
    FILE* fp;
    fp = fopen("linkedlist.bin", "rb");// opening the file in reading mode
    if(fp==NULL){
        printf("Error!\n");
        exit(0);
    }

    Node* iter = NULL;
    while(!feof(fp)) {
        char type[20];
        // reading the type at first which is 20 byte
        if(fread(type, 20, 1, fp) != 1) {
            break;
        }
        //if we can read the type
        fseek(fp, -20, SEEK_CUR); // move back the file pointer 20 byte which is size of 'type'
        Node* node = (Node*)malloc(sizeof(Node)); //creating a new node for the data
        node->next = NULL;
        // if type is Asset1 
        if(strcmp(type, "Asset1") == 0) {
            Asset1* asset = (Asset1*)malloc(sizeof(Asset1));
            fread(asset, sizeof(Asset1), 1, fp);
            node->data = asset;
        } 
        // if type is Asset2
        else if(strcmp(type, "Asset2") == 0) {
            Asset2* asset = (Asset2*)malloc(sizeof(Asset2));
            fread(asset, sizeof(Asset2), 1, fp);
            node->data = asset;
        } 
        // if type is Asset3
        else if(strcmp(type, "Asset3") == 0) {
            Asset3* asset = (Asset3*)malloc(sizeof(Asset3));
            fread(asset, sizeof(Asset3), 1, fp);
            node->data = asset;
        }
        // if type is Asset4 
        else if(strcmp(type, "Asset4") == 0) {
            Asset4* asset = (Asset4*)malloc(sizeof(Asset4));
            fread(asset, sizeof(Asset4), 1, fp);
            node->data = asset;
        }
        // if head is NULL
        if(*head == NULL) {
            *head = node;
        } 
        else {
            iter->next = node;
        }
        iter = node;
    }
    fclose(fp);
}

// free function
void freeLinkedList(Node* head) {
  Node* temp = head;
  while (temp != NULL) {
    Node* next = temp->next;
    free(temp->data);
    free(temp);
    temp = next;
  }
}
int main() {

    srand(time(0));
    
    // fill the linked list
    Node* head = NULL;
    fillLinkedList(&head);
    
    // serialize the linked list and write it to the binary file
    serializeLinkedList(head);
    
    // reading the binary file
    Node* new_head = NULL;
    deserializeLinkedList(&new_head);

    // printing the data of each node for the video just after filling the nodes with the datas in the binary file
    Node*temp = new_head;
    while(temp!=NULL){
        if (strcmp(((Asset1*)temp->data)->type, "Asset1") == 0) {
            Asset1* asset = (Asset1*)temp->data;
            printf(">Type: %s<\nivals: %d\nsvals: %f\n************\n", asset->type, asset->ivals[0], asset->svals[0]);
        }
        else if (strcmp(((Asset2*)temp->data)->type, "Asset2") == 0) {
            Asset2* asset = (Asset2*)temp->data;
            printf(">Type: %s<\nivals1: %d \nivals2: %d\nsvals1: %f \nsvals2: %f\n************\n", asset->type, asset->ivals[0], asset->ivals[1], asset->svals[0], asset->svals[1]);
        }
        else if (strcmp(((Asset3*)temp->data)->type, "Asset3") == 0) {
            Asset3* asset = (Asset3*)temp->data;
            printf(">Type: %s<\nstring1: %s \nstring2: %s\n************\n", asset->type, asset->string1, asset->string2);
        }
        else if (strcmp(((Asset4*)temp->data)->type, "Asset4") == 0) {
            Asset4* asset = (Asset4*)temp->data;
            printf(">Type: %s<\nvalue1: %f \nvalue2: %f \nvalue3: %f\n************\n", asset->type, asset->value1, asset->value2, asset->value3);
        }
        temp = temp->next;    
    }

    // free head and new_head
    freeLinkedList(head);
    freeLinkedList(new_head);
    return 0;
}