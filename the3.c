#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "the3.h"

/*
    Create a cache by reading inputs from stdin
*/
Cache* createCache()
{
    int i;
    int isFreqNodePlaced;
    int stringCompare;

    /* char* videoName, domainName; */
    Cache* cache;
    CacheNode* node;

    DomainFreqNode* domainFreqNode;
    DomainFreqNode* domainFreqNodeIterator;

    char Line[1000];
    char* token;
    int tokenSize;
    int tokenNum;

    /* Allocate memory for the cache */
    cache = (Cache*)malloc(sizeof(Cache));

    /* Allocate memory for first node */
    cache->head = (CacheNode*)malloc(sizeof(CacheNode));
    cache->tail = cache->head;

    node = cache->head;

    isFreqNodePlaced = 0;
    cache->currentSize = 0;

    scanf("%d %d\n", &cache->cacheLimit, &cache->mediaCount);

    for(i=0; i<cache->mediaCount; i++)
    {

        /* Get line from stdin */
        fgets(Line, 1000, stdin);


        /* First token is the name of the media */
            token = strtok(Line, " ");
            tokenSize = strlen(token);

            /* Allocate area for node's media name */
            node->media.name = (char*)malloc(sizeof(char) * (tokenSize + 1));
            strcpy(node->media.name, token);
            /* Add ending character */
            node->media.name[tokenSize] = '\0';

        /* Second token is the size of the media, it is always an integer */
            token = strtok(NULL, " ");
            tokenNum = atoi(token);
            node->media.size = tokenNum;
            cache->currentSize += node->media.size;

        /* Arrange head and tail with the first pair */
            token = strtok(NULL, " ");
            tokenSize = strlen(token);

            node->domainFreqList = (DomainFreqList*)malloc(sizeof(DomainFreqList));
            /* 
               Allocate memory for first node of domain freq list
               assign resulting pointer to head and the tail
            */
            node->domainFreqList->head = (DomainFreqNode*)malloc(sizeof(DomainFreqNode));
            node->domainFreqList->tail = node->domainFreqList->head;

            /*
               Allocate memory for the name of the domain and 
               assign it to the freq list node
            */
            node->domainFreqList->head->name = (char*)malloc(sizeof(char) * (tokenSize + 1));
            strcpy(node->domainFreqList->head->name, token);
            node->domainFreqList->head->name[tokenSize] = '\0';

            /*
                Obtain the frequency and assign the freq field
            */
            token = strtok(NULL, " ");
            tokenNum = atoi(token);
            node->domainFreqList->head->freq = tokenNum;

            /* Obtain second domain name */
            token = strtok(NULL, " ");

        /* Remaining tokens are groups of two that are domain and freq pairs */
            while(token)
            {
                /* Obtain domain name */
                tokenSize = strlen(token);

                /* Allocate memory for the domain freq node that is going to be added*/
                domainFreqNode = (DomainFreqNode*)malloc(sizeof(DomainFreqNode));

                /* Get domain name */
                domainFreqNode->name = (char*)malloc(sizeof(char) * (tokenSize + 1));
                strcpy(domainFreqNode->name, token);
                domainFreqNode->name[tokenSize] = '\0';

                /* Get domain freq */
                token = strtok(NULL, " ");
                tokenNum = atoi(token);
                domainFreqNode->freq = tokenNum;

                /* 
                    Now traverse the domain frequency list and place new node
                    to the appropriate position
                */
               domainFreqNodeIterator = node->domainFreqList->head;
               while(domainFreqNodeIterator)
               {
                    /* First check frequencies list is sorted in descending order */
                    if(domainFreqNode->freq > domainFreqNodeIterator->freq)
                    {
                        /* Node placed before the iterator */

                        /* 
                           If iterator is at the head
                           new node becomes the head
                        */
                        if(domainFreqNodeIterator == node->domainFreqList->head)
                        {
                            domainFreqNode->next = node->domainFreqList->head;
                            node->domainFreqList->head = domainFreqNode;
                            domainFreqNode->next->prev = domainFreqNode;
                        }
                        /*
                            If iterator is ahead of the head
                        */
                        else
                        {
                            domainFreqNode->prev = domainFreqNodeIterator->prev;
                            domainFreqNodeIterator->prev->next = domainFreqNode;
                            domainFreqNodeIterator->prev = domainFreqNode;
                            domainFreqNode->next = domainFreqNodeIterator;
                        }

                        /* We must stop traversing further */
                        isFreqNodePlaced = 1;
                        break;
                    }
                    else if (domainFreqNode->freq == domainFreqNodeIterator->freq)
                    {
                        /* To break the tie, we compare their names ascii ascending order */
                        stringCompare = strcmp(domainFreqNode->name, domainFreqNodeIterator->name);

                        /*
                            If first string is lower, It will be placed
                            before the iterator
                        */
                        if (stringCompare < 0)
                        {
                            /* 
                                If iterator is at the head
                                new node becomes the head
                            */
                            if(domainFreqNodeIterator == node->domainFreqList->head)
                            {
                                domainFreqNode->next = node->domainFreqList->head;
                                node->domainFreqList->head = domainFreqNode;
                                domainFreqNode->next->prev = domainFreqNode;
                            }
                            /*
                                If iterator is ahead of the head
                            */
                            else
                            {
                                domainFreqNode->prev = domainFreqNodeIterator->prev;
                                domainFreqNodeIterator->prev->next = domainFreqNode;
                                domainFreqNodeIterator->prev = domainFreqNode;
                                domainFreqNode->next = domainFreqNodeIterator;
                            }

                            /* We must stop traversing further */
                            isFreqNodePlaced = 1;
                            break;                            
                        }
                    }
                    if(domainFreqNode->freq < domainFreqNodeIterator->freq)
                    {
                        /* 
                           If iterator is at the tail
                           new node becomes the head
                        */
                        if(domainFreqNodeIterator->next == NULL)
                        {
                            domainFreqNodeIterator->next = domainFreqNode;
                            domainFreqNode->prev = domainFreqNodeIterator;
                            domainFreqNode->next = NULL;

                            break;
                        }
                    }

                    /* Carry on iteration */    
                    domainFreqNodeIterator = domainFreqNodeIterator->next;
               }

               /*
                    If we could not place while iterating, it means that
                    we have to place the new node to the tail
                */
               if(isFreqNodePlaced == 0)
               {
                    node->domainFreqList->tail->next = domainFreqNode;
                    domainFreqNode->prev = node->domainFreqList->tail;
                    node->domainFreqList->tail = domainFreqNode;
               }

                /* Obtain next domain name */
                token = strtok(NULL, " ");
            }

        if(i != cache->mediaCount - 1)
        {
            node->next = (CacheNode*)malloc(sizeof(CacheNode));
            cache->tail = node->next;
            cache->tail->prev = node;
            node = node->next;
        }
        
    }

    return cache;
}

/*
    Prints cache information and its contents
*/
void printCache(Cache* cache)
{
    CacheNode* currentcachenode;
    DomainFreqNode* currentfreqnode;
    
    if (cache->head==NULL){
        printf("The Cache is Empty");
    }
    else{
        printf("-------------- Cache Information --------------\n");
        printf("Cache Limit: %d KB\n",cache->cacheLimit);
        printf("Current Size: %d KB\n",cache->currentSize);
        printf("Media Count: %d\n",cache->mediaCount);
        printf("Cache Media Info:\n");
        currentcachenode=cache->head;
        while(currentcachenode!=NULL){
            printf("    Name: %s    Size: %d KB\n",currentcachenode->media.name,currentcachenode->media.size);
            printf("    ------- Media Domain Frequencies -------\n");
            currentfreqnode=currentcachenode->domainFreqList->head;
            while(currentfreqnode!=NULL){
                printf("        Name: %s    Freq: %d\n",currentfreqnode->name,currentfreqnode->freq);
                currentfreqnode=currentfreqnode->next;
            }
            printf("    ----------------------------------------\n");
            currentcachenode=currentcachenode->next;
        }
        printf("----------------------------------------------");
    }
    
}    
        
        



/*
    Adds media to the cache
*/
CacheNode* addMediaRequest(Cache* cache, Media media, char* domain)
{
    int ctrl,domainctrl;
    CacheNode* newvideo;
    CacheNode* target;
    CacheNode* gonnadlt;
    DomainFreqNode* targetdomain;
    DomainFreqNode* newdomain;
    DomainFreqNode* newdomain2;
    DomainFreqNode* compdomain;
    target=cache->head;
    ctrl=0;
    while(target){
        if(strcmp(target->media.name,media.name)==0){
            ctrl=1;
            break;
        }
        else{
            if (target->next==NULL){
                break;
            }
            else{
                target=target->next;
            }
        }
    }
    /*video varsa*/
    if(ctrl){
        /*videoyu başa atma*/
        if(target->next==NULL){
            target->prev->next=NULL;
            target->next=cache->head;
            cache->tail=target->prev;
            target->prev=NULL;
            cache->head=target;
        }
        else if(target->prev==NULL){
        }
        else{
            target->next->prev=target->prev;
            target->prev->next=target->next;
            target->next=cache->head;
            cache->head->prev=target;
            cache->head=target;
            target->prev=NULL;
        }
        targetdomain=target->domainFreqList->head;
        domainctrl=0;
        /*domain varsa bulma arttırma*/
        while(targetdomain){
            if (strcmp(targetdomain->name,domain)==0){
                domainctrl=1;
                (targetdomain->freq)++;
                break;
            }
            else{
                if (targetdomain->next==NULL){
                    break;
                }
                else{
                    targetdomain=targetdomain->next;
                }
            }
        }
        /*arttırılan domaini yeni sırasına ekleme*/
        if(domainctrl==1){
            if (targetdomain->prev!=NULL){
                compdomain=targetdomain->prev;
                while(targetdomain->freq>compdomain->freq){
                        if(targetdomain->next==NULL){
                            targetdomain->prev=compdomain->prev;
                            compdomain->prev->next=targetdomain;
                            compdomain->prev=targetdomain;
                            compdomain->next=NULL;
                            target->domainFreqList->tail=compdomain;
                            compdomain=targetdomain->prev;
                        }
                        else if(compdomain->prev==NULL){
                            compdomain->next=targetdomain->next;
                            targetdomain->next->prev=compdomain;
                            targetdomain->next=compdomain;
                            targetdomain->prev=NULL;
                            compdomain->prev=targetdomain;
                            target->domainFreqList->tail=targetdomain;
                            break;
                        }
                        else{
                            compdomain->prev->next=targetdomain;
                            compdomain->next=targetdomain->next;
                            targetdomain->prev=compdomain->prev;
                            targetdomain->next->prev=compdomain;
                            targetdomain->next=compdomain;
                            compdomain->prev=targetdomain;
                            compdomain=targetdomain->prev;
                        }
                }
                if(targetdomain->prev!=NULL){
                    while(targetdomain->freq==compdomain->freq && strcmp(compdomain->name,targetdomain->name)>0){
                        if(targetdomain->next==NULL){
                        targetdomain->prev=compdomain->prev;
                        targetdomain->next=compdomain;
                        compdomain->prev->next=targetdomain;
                        compdomain->prev=targetdomain;
                        compdomain->next=NULL;
                        target->domainFreqList->tail=compdomain;
                        compdomain=targetdomain->prev;
                        }
                        else if(compdomain->prev==NULL){
                            compdomain->next=targetdomain->next;
                            targetdomain->next->prev=compdomain;
                            targetdomain->next=compdomain;
                            targetdomain->prev=NULL;
                            compdomain->prev=targetdomain;
                            target->domainFreqList->tail=targetdomain;
                            break;
                        }
                        else{
                            compdomain->prev->next=targetdomain;
                            compdomain->next=targetdomain->next;
                            targetdomain->prev=compdomain->prev;
                            targetdomain->next->prev=compdomain;
                            targetdomain->next=compdomain;
                            compdomain->prev=targetdomain;
                            compdomain=targetdomain->prev;
                        }
                    }
                }
            }
            return target;
        }
        /*domain yoksa oluşturma*/
        else if(domainctrl==0){
            newdomain=(DomainFreqNode*)malloc(sizeof(DomainFreqNode));
            newdomain->name=domain;
            newdomain->freq=1;
            target->domainFreqList->tail->next=newdomain;
            newdomain->prev=target->domainFreqList->tail;
            target->domainFreqList->tail=newdomain;
            newdomain->next=NULL;
            compdomain=newdomain->prev;
            if (newdomain->prev!=NULL){
                while(newdomain->freq==compdomain->freq && strcmp(compdomain->name,newdomain->name)>0){
                    if(newdomain->next==NULL){
                        newdomain->prev=compdomain->prev;
                        newdomain->next=compdomain;
                        compdomain->prev->next=newdomain;
                        compdomain->prev=newdomain;
                        compdomain->next=NULL;
                        target->domainFreqList->tail=compdomain;
                        compdomain=newdomain->prev;
                    }
                    else if(compdomain->prev==NULL){
                        compdomain->next=newdomain->next;
                        newdomain->next->prev=compdomain;
                        newdomain->next=compdomain;
                        newdomain->prev=NULL;
                        compdomain->prev=newdomain;
                        target->domainFreqList->tail=newdomain;
                        break;
                    }
                    else{
                        compdomain->prev->next=newdomain;
                        compdomain->next=newdomain->next;
                        newdomain->prev=compdomain->prev;
                        newdomain->next->prev=compdomain;
                        newdomain->next=compdomain;
                        compdomain->prev=newdomain;
                        compdomain=newdomain->prev;
                    }
                }
                if(newdomain->prev!=NULL){
                    while(newdomain->freq==compdomain->freq && strcmp(compdomain->name,newdomain->name)>0){
                        if(newdomain->next==NULL){
                            newdomain->prev=compdomain->prev;
                            newdomain->next=compdomain;
                            compdomain->prev->next=newdomain;
                            compdomain->prev=newdomain;
                            compdomain->next=NULL;
                            target->domainFreqList->tail=compdomain;
                            compdomain=newdomain->prev;
                        }
                        else if(compdomain->prev==NULL){
                            compdomain->next=newdomain->next;
                            newdomain->next->prev=compdomain;
                            newdomain->next=compdomain;
                            newdomain->prev=NULL;
                            compdomain->prev=newdomain;
                            target->domainFreqList->tail=newdomain;
                            break;
                        }
                        else{
                            compdomain->prev->next=newdomain;
                            compdomain->next=newdomain->next;
                            newdomain->prev=compdomain->prev;
                            newdomain->next->prev=compdomain;
                            newdomain->next=compdomain;
                            compdomain->prev=newdomain;
                            compdomain=newdomain->prev;
                        }
                    }
                }
            }
        }
        return target;
    }
    /*video yoksa*/
    else{
        cache->currentSize=cache->currentSize+media.size;
        cache->mediaCount++;
        newvideo=(CacheNode*)malloc(sizeof(CacheNode));
        newdomain2=(DomainFreqNode*)malloc(sizeof(DomainFreqNode));
        newvideo->media=media;
        newdomain2->name=domain;
        newdomain2->freq=1;
        newvideo->domainFreqList=(DomainFreqList*)malloc(sizeof(DomainFreqNode));
        newvideo->domainFreqList->head=newdomain2;
        newvideo->domainFreqList->tail=newdomain2;
        newdomain2->next=NULL;
        newdomain2->prev=NULL;
        newvideo->next=cache->head;
        cache->head->prev=newvideo;
        cache->head=newvideo;
        newvideo->prev=NULL;
        /*size yeterli değilse silme*/
        while(cache->currentSize>cache->cacheLimit){
            gonnadlt=cache->tail;
            gonnadlt->prev->next=NULL;
            cache->tail=gonnadlt->prev;
            gonnadlt->prev=NULL;
            cache->currentSize=(cache->currentSize)-(gonnadlt->media.size);
            cache->mediaCount=cache->mediaCount - 1;
            free(gonnadlt);
        }
        
        return newvideo;
    }
    return NULL;
}

/*
    Finds the corresponding media's node in the cache
    Return NULL if it is not found
*/
CacheNode* findMedia(Cache* cache, char* name)
{
    CacheNode* current;
    current=cache->head;
    while(current){
        if(strcmp(current->media.name,name)==0){
            return current;
        }
        else{
            current=current->next;
            
        }
    }
    return NULL;
}

/*
    Finds a media from its name and deletes it's node from the cache
    Do not do anything if media is not found
*/
void deleteMedia(Cache* cache, char* name)
{
    CacheNode* current;
    int ctrldelete=0;
    current=cache->head;
    while(current){
        if(strcmp(current->media.name,name)==0){
            ctrldelete=1;
            break;
        }
        else{
            current=current->next;
        }
    }
    if(ctrldelete){
        if (cache->mediaCount==1){
            cache->head=NULL;
            cache->tail=NULL;
        }
        else{
            cache->currentSize=(cache->currentSize)-(current->media.size);
            cache->mediaCount=cache->mediaCount-1;
            if(current->prev==NULL){
                current->next->prev=NULL;
                cache->head=current->next;
                current->next=NULL;
            }
            else if(current->next==NULL){
                current->prev->next=NULL;
                cache->tail=current->prev;
                current->prev=NULL;
            }
            else{
                current->next->prev=current->prev;
                current->prev->next=current->next;
                current->next=NULL;
                current->prev=NULL;
            }
        free(current);
        }    
    
    }

}