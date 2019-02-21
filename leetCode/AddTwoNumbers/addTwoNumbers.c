#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

struct ListNode{ 
    int val;
    struct  ListNode* next;
};

typedef struct ListNode nodo_t;


struct ListNode* addTwoNumbers(struct ListNode*, struct ListNode*);
void setSameSize(struct ListNode*, struct ListNode*);
struct ListNode* string2list(char * );

int main(int argc, char ** argv){
    FILE * fp = NULL;
    char *tmp1, *tmp2;
    char test;
    int len = 0;
    struct ListNode * l1, * l2, * ret;
    

    if(argc != 2){
        fprintf(stderr, "usage: %s <fileIn>\n", argv[0]);
        return 0;
    }

    fp = fopen(argv[1], "r");
    if(fp == NULL){
        fprintf(stderr, "%s\n", strerror(errno));
        return 0;
    }
    
    /* first number */
    while(!feof(fp)){
        fscanf(fp, "%c", &test);
        if(test == '\n')
            break;
        len++;
    }
    len++;
    tmp1 = (char * ) malloc(len);
    fseek(fp, 0, SEEK_SET);
    if(fgets(tmp1, len, fp) == NULL){
        fprintf(stderr, "codifica errata!");
        fclose(fp);
        return 0;
    }
    fseek(fp, 1, SEEK_CUR);
    
    /* second number */
    len = 0;
    while(!feof(fp)){
        fscanf(fp, "%c", &test);
        if(test == '\n')
            break;
        len++;
    }
    len++;
    tmp2 = (char * ) malloc(len);
    fseek(fp, 1+strlen(tmp1), SEEK_SET);
    if(fgets(tmp2, len, fp) == NULL){
        fprintf(stderr, "codifica errata!");
        fclose(fp);
        return 0;
    }
    fclose(fp);
    /* reading phase take O(m+n) */


    printf("============> the numbers %s %s <===============\n", tmp1, tmp2);

    // O(n+m)
    l1 = string2list(tmp1);
    l2 = string2list(tmp2);


    free(tmp1);
    free(tmp2);
    
    ret = addTwoNumbers(l1, l2);

    printf("List\n");
    while(ret != NULL){
        printf("%d\n", ret->val);
        ret = ret->next;
    }

    return 0;
}


struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    
    int resto = 0, riporto = 0, tmp = 0;
    struct ListNode * ret = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode * retHead = ret, *prev;
   
    setSameSize(l1,l2);

    while(l1 != NULL){
        
        ret->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        tmp = l1->val + l2->val + riporto;
        if( tmp > 9 ){
            riporto = tmp/10;
            resto = tmp - 10*riporto;
        }else{
            riporto = 0;
            resto = tmp;
        }
        ret->val = resto;
        l1 = l1->next;
        l2 = l2->next;
        prev = ret;
        ret = ret->next;
        ret->val = 0;
        ret->next = NULL;
    }
    if(riporto != 0){
        ret->val += riporto;
    }else{
        free(prev->next);
        prev->next = NULL;
    }
    return retHead;
}

struct ListNode* string2list(char * str){
    int i = 0;
    struct ListNode * tmp = (struct ListNode *)malloc(sizeof(struct ListNode));
    struct ListNode * head = tmp; 
    tmp->val = str[strlen(str)-1] - '0';
    tmp->next = NULL;
    for(i = strlen(str)-1; i > 0; i--){
        tmp->next = (struct ListNode *)malloc(sizeof(struct ListNode));
        tmp = tmp->next;
        tmp->val = str[i-1] - '0';
        tmp->next = NULL;
    }
    return head;
}


/* O(n+m)*/
void setSameSize(struct ListNode* l1, struct ListNode* l2){
    struct ListNode * cursor;
    struct ListNode * prev;
    int len1 = 0, len2 = 0, i = 0;
    
    cursor = l1;
    while(cursor != NULL){
        len1++;
        cursor = cursor->next;
    }
    
    cursor = l2;
    while(cursor != NULL){
        len2++;
        cursor = cursor->next;
    }
    
    if(len1 > len2){
        cursor = l2;
        for(i = 0; i < len1; i++){
            if( i >= len2){
                cursor->val = 0;
                cursor->next = NULL;
            }
            if(cursor->next == NULL){
                cursor->next = (struct ListNode *)malloc(sizeof(struct ListNode));
            }

            prev = cursor;
            cursor = cursor->next;
        }
    }
    else{
        cursor = l1;
        for(i = 0; i < len2; i++){
            if( i >= len1){
                cursor->val = 0;
                cursor->next = NULL;
            }
            if(cursor->next == NULL){
                cursor->next = (struct ListNode *)malloc(sizeof(struct ListNode));
            }

            prev = cursor;
            cursor = cursor->next;
        }
    }
   
    if(prev->next != NULL){ 
        free(prev->next);
        prev->next = NULL;
    }

}

