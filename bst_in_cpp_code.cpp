#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <math.h>
#include <iomanip>

using namespace std;





typedef struct node Node;

struct node {
	int lvl;
	double data;
	Node *right;
	Node *left;
};

Node *createzero (){
	
	Node *nev;
	nev = new (Node);
	nev->lvl = 0;
	nev->data = 0;
	nev->right = NULL;
	nev->left = NULL;
	
	return nev;
}

void addelement (double value, Node **root, int &level){
	
	if (*root == NULL){
		Node *tmp = createzero();
		tmp->lvl = level;
		tmp->data = value;
		*root = tmp;
	}
		
	else if (value < (*root)->data){
		level++;
		addelement (value, &((*root)->left), level);
	}
	
	else if (value >= (*root)->data){
		level++;
		addelement (value, &((*root)->right), level);
	}
}

Node *findelement (double value, Node *root){
	
	if (root != NULL){
		
		if (value == root->data){
			return root;
		}
		
		else if (value < root->data){
			return findelement (value, root->left);
		}
		
		else if (value >= root->data){
			return findelement (value, root->right);
		}
	}
	
	else return NULL;
}

void deleteelement (double value, Node **root){
	
	Node *current = findelement (value, *root);
	Node *temp = NULL;
	Node *temp2 = NULL;
	
	if (current == NULL)
	cout << "Brak elementu do usuniecia!";
	
	else{
		
		if (current->left == NULL && current->right == NULL){
			delete (current);
		}
		
		else if (current->left != NULL && current->right != NULL){
			temp = current->left;
			while (temp->right != NULL){
				temp = temp->right;
			}
			current->data = temp->data;
			
			if (temp->left == NULL && temp->right == NULL)
			delete (temp);
			else{
				if (temp->left != NULL){
					temp2 = temp->left;
					temp->data = temp2->data;
					temp->left = temp2->left;
					temp->right = temp2->right;
					delete (temp2);
				}
				else{
					temp2 = temp->right;
					temp->data = temp2->data;
					temp->left = temp2->left;
					temp->right = temp2->right;
					delete (temp2);
				}
			}
		}
		
		else{
			if (current->left != NULL){
				temp2 = current->left;
				current->data = temp2->data;
				current->left = temp2->left;
				current->right = temp2->right;
				delete (temp2);
			}
			else{
				temp2 = current->right;
				current->data = temp2->data;
				current->left = temp2->left;
				current->right = temp2->right;
				delete (temp2);
			}
		}
	}
}

void inorder (Node *root){
	
	if (root != NULL){
		inorder (root->left);
		cout << " " << (root->data);
		inorder (root->right);
	}
}

void preorder (Node *root){
	
	if (root != NULL){
		cout << " " << (root->data);
		preorder (root->left);
		preorder (root->right);
	}
}

void postorder (Node *root){
	
	if (root != NULL){
		postorder (root->left);
		postorder (root->right);
		cout << " " << (root->data);
	}
}

void countelement (double value, Node *root, int &licznik){
	
	if (root != NULL){
		countelement (value, root->left, licznik);
		if (value == (root->data)) licznik++;
		countelement (value, root->right, licznik);
	}
}

void draw (Node *root, int width){
	
    if (root != NULL){
        draw (root->left, width + 4);
        if (width > 0) cout << setw(width) << " ";
        cout << root->data << endl;
        draw (root->right, width + 4);
    }
}





typedef struct wezel Wezel;

struct wezel {
	double liczba;
	Wezel *next;
	Wezel *prev;
};

Wezel *zrobzero (){
	
	Wezel *nev;
	nev = new (Wezel);
	nev->liczba = 0;
	nev->next = NULL;
	nev->prev = NULL;
	
	return nev;
}

Wezel *dodajzero (Wezel **head, Wezel **tail){
	
	Wezel *tmp = zrobzero();
	
	if (*head == NULL)
		*head = tmp;
	else{
		Wezel *pom = *head;
		while (pom->next != NULL)
			pom = pom->next;
		pom->next = tmp;
		tmp->prev = pom;
	}
	
	*tail = tmp;
	
	return *tail;
}

void usunwezel (Wezel **current, Wezel **head){
	
	if ((*current) == (*head)){
		(*head) = ((*current)->next);
		((*current)->next)->prev = NULL;
	}
	
	else {
		((*current)->next)->prev = ((*current)->prev);
		((*current)->prev)->next = ((*current)->next);
	}
	
	delete (*current);
}

Wezel *wlewo (Wezel **current){
	
	*current = (*current)->prev;
	
	return *current;
}

Wezel *wprawo (Wezel **current){
	
	*current = (*current)->next;
	
	return *current;
}

void usunwszystko (Wezel **head){
	
	if (*head == NULL);
	
	else{
		Wezel *pom = *head;
		while (pom != NULL){
			*head = pom->next;
			delete (pom);
			pom = *head;
		}
	}
}

void pokazwszystko (Wezel *head){
	
	if (head == NULL);
	
	else{
		Wezel *pom = head;
		while (pom != NULL){
			cout << pom->liczba << ";";
			pom = pom->next;
		}
	}
}

double srednia (Wezel *head){
	
	if (head == NULL)
		return 0;
	else{
		double suma = 0;
		double n = 0;
		Wezel *pom = head;
		while (pom != NULL){
			suma = suma + 1/(pom->liczba);
			n++;
			pom = pom->next;
		}
		double sre = n/suma;
		return sre;
	}
}





void savelevel (Node *root, int level, Wezel **head, Wezel **tail){
	
	if (root != NULL){
		savelevel (root->left, level, &(*head), &(*tail));
		if (level == (root->lvl)){
			dodajzero (&(*head), &(*tail));
			(*tail)->liczba = root->data;
		}
		savelevel (root->right, level, &(*head), &(*tail));
	}
}

void showlevel (Node *root, int level, Wezel **head, Wezel **tail){
	
	savelevel (root, level, &(*head), &(*tail));
	
	pokazwszystko (*head);
	
	double sre = srednia (*head);
	
	cout << " srednia harmoniczna : " << sre << endl;
	
	usunwszystko (&(*head));
}

void measure (Node *root, int &height){
	
	if (root != NULL){
        measure (root->left, height);
        if (root->lvl > height)
			height = root->lvl;
        measure (root->right, height);
    }
}





void count (Node *root, double &podsum, double &podile){
	
	if (root != NULL){
        count (root->left, podsum, podile);
        podsum = podsum + root->data;
        podile++;
        cout << root->data << ";";
        count (root->right, podsum, podile);
    }
}

void step (Node *root){
	
	if (root != NULL){
        step (root->left);
        double podsum = 0;
        double podile = 0;
        double podsre = 0;
        cout << "poddrzewo : ";
        count (root, podsum, podile);
        podsre = podsum/podile;
        cout << " srednia arytmetyczna : " << podsre << endl;
        step (root->right);
    }
}











int main (void){
	
	cout << "JESTEM DRZEWEM." << endl;
	
	Wezel *head = NULL;
	Wezel *tail = NULL;
	
	Node *root = NULL;
	double value = 0;
	Node *check = NULL;
	int licznik = 0;
	int level = 0;
	int height = 0;
	int i = 1000;
	
	while (i != 0){
		
		cout << "KONIEC? 0-tak, 1-nie" << endl;
		cin >> i;
		
		if (i != 0){
			
			system("cls");
			
			cout << "CO CHCESZ ZROBIC:" << endl
			<< "1-dodaj" << endl
			<< "2-usun" << endl
			<< "3-znajdz element" << endl
			<< "4-licz wystapienia" << endl
			<< "5-inorder" << endl
			<< "6-preorder" << endl
			<< "7-postorder" << endl
			<< "8-rysuj drzewo" << endl
			<< "9-srednie harmoniczne poziomow" << endl
			<< "10-srednie arytmetyczne poddrzew" << endl
			<< "0-KONIEC" << endl;
			
			cin >> i;
			
			if (i == 1){
				
				cout << "Podaj wartosc do dodania: ";
				cin >> value;
				level = 0;
				addelement (value, &root, level);
			}
			
			else if (i == 2){
				
				cout << "Podaj wartosc do usuniecia: ";
				cin >> value;
				deleteelement (value, &root);
			}
			
			else if (i == 3){
				
				cout << "Podaj wartosc do znalezienia: ";
				cin >> value;
				check = findelement (value, root);
				if (check == NULL)
					cout << "nie" << endl;
				else
					cout << "tak" << endl;
			}
			
			else if (i == 4){
				
				cout << "Podaj wartosc do liczenia wystapien: ";
				cin >> value;
				licznik = 0;
				countelement (value, root, licznik);
				cout << "Ilosc wystapien: " << licznik << endl;
			}
			
			else if (i == 5){
				inorder (root);
			}
			
			else if (i == 6){	
				preorder (root);
			}
			
			else if (i == 7){
				postorder (root);
			}
			
			else if (i == 8){
				draw (root, 4);
			}
			
			else if (i == 9){
				
				measure (root, height);
				level = 0;
				while (level <= height){
					cout << "poziom " << level << " : ";
					showlevel (root, level, &head, &tail);
					level++;
				}
			}
			
			else if (i == 10){
				step (root);
			}
		}
	}
	
	system ("pause");
	return 0;
}




	
