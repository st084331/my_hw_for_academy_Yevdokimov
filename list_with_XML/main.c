#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

void push(Node **head, int data) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    tmp->value = data;
    tmp->next = (*head);
    (*head) = tmp;
}

int pop(Node **head) {
    Node* prev = NULL;
    int val;
    if (head == NULL) {
        exit(-1);
    }
    prev = (*head);
    val = prev->value;
    (*head) = (*head)->next;
    free(prev);
    return val;
}

Node *getNth(Node *head, int n) {
    int counter = 0;
    while (counter < n && head) {
        head = head->next;
        counter++;
    }
    return head;
}

void print_list(Node *head){
    Node* current = head;
    while(current != NULL){
        printf("%d ", current->value);
        current = current->next;
    }
}

char* read_file_ascii(const char* path){
    FILE* fp = fopen(path, "r");
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char* buf = (char*) malloc(sizeof(char) * (size+1));
    fread(buf, sizeof(char), size, fp);
    buf[size] = "\0";
    return buf;
}


// УТОЧНЕНИЕ
// В ФАЙЛЕ XML ЭЛЕМЕНТЫ ДАНЫ В ПОРЯДКЕ ЗАПИСИ В СПИСОК, ТО ЕСТЬ ПЕРВЫЙ ЭЛЕМЕНТ ЭТО НЕ ГОЛОВА, А КОНЕЦ СПИСКА.
//

void xml_to_list(Node **head, char *path){
    char *source = read_file_ascii(path);
    int k = 0;
    for (int i = 0; i < strlen(source) - 5; i++) {
        if (source[i] == '>') {
            if (source[i + 1] != '\n') {
                float number = 0;
                i++;
                float deg = 0;
                while (source[i] != '<') {
                    number = number * powf(10, deg) + (float) (source[i] - '0');
                    deg++;
                    i++;
                }
                push(head, (int) number);
                k++;
            }
        }
    }
    free(source);
}

void list_to_xml(Node **head, char *path){
    FILE* fp = fopen(path, "w");
    char buf[100000];
    strcat(buf, "<List>\n   <Elements>\n");
    int n = 0;
    while(getNth(*head, n) != NULL){
        n++;
    }
    for(int i = 0; i < n; i++){
        char new_str[100];
        sprintf(new_str, "          <Element%d>%d</Element%d>\n", i+1, getNth(*head, n-i-1)->value,i+1);
        strcat(buf, new_str);
    }
    strcat(buf, "   </Elements>\n</List>");
    fputs(buf,fp);
    fclose(fp);
}

int main() {
    Node *head = NULL;
    xml_to_list(&head, "/Users/akabynda/CLionProjects/list_with_XML/programmers.xml");
    print_list(head);
    printf("\n");
    list_to_xml(&head, "/Users/akabynda/CLionProjects/list_with_XML/list_to_xml.xml");
    return 0;
}
