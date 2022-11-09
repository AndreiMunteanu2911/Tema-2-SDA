#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TreeMap.h"
#define MAX(a, b) (((a) >= (b))?(a):(b))
/* Creeaza un arbore cu o serie de metode asociate
 *
 * return: arborele creat
 */
TTree* createTree(void* (*createElement)(void*),
	void (*destroyElement)(void*),
	void* (*createInfo)(void*),
	void (*destroyInfo)(void*),
	int compare(void*, void*)) {
	TTree* tree = (TTree*)malloc(sizeof(TTree));
	tree->size = 0;
	tree->root = NULL;
	tree->createElement = createElement;
	tree->destroyElement = destroyElement;
	tree->createInfo = createInfo;
	tree->destroyInfo = destroyInfo;
	tree->compare = compare;
	return tree;
}
/* Verifica daca un arbore este gol (vid)
 * 		1 - daca arborele este gol
 * 		0 - in caz contrar
 */
int isEmpty(TTree* tree) {
	if (tree->root == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
/* Cauta un anumit element in interiorul unui arbore
 *
 * tree: structura cu metodele asociate arborelui
 *   !folosit pentru a putea compara elementul curent cu cel cautat
 *
 * x: radacina arborelui curent (in care se face cautarea)
 * elem: elementul ce trebuie cautat
 */
TreeNode* search(TTree* tree, TreeNode* x, void* elem) {
	if (x == NULL)
	{
		return NULL;
	}
	if (tree->compare(x->elem, elem) == 0)
	{
		return x;
	}
	TreeNode* left = search(tree, x->left, elem);
	TreeNode* right = search(tree, x->right, elem);
	if (left != NULL && right == NULL)
	{
		return left;
	}
	if (left == NULL && right != NULL)
	{
		return right;
	}
	if (left == NULL && right == NULL)
	{
		return NULL;
	}
}
/* Gaseste nodul cu elementul minim dintr-un arbore
 * avand radacina in x
 */
TreeNode* minimum(TreeNode* x) {
	if (x == NULL)
	{
		return NULL;
	}
	TreeNode* current = x;
	while (current->left != NULL)
	{
		current = current->left;
	}
	return current;
}
/* Gaseste nodul cu elementul maxim dintr-un arbore
 * avand radacina in x
 */
TreeNode* maximum(TreeNode* x) {
	if (x == NULL)
	{
		return NULL;
	}
	TreeNode* current = x;
	while (current->right != NULL)
	{
		current = current->right;
	}
	return current;
}
/* Functie pentru gasirea succesorului unui nod
 * (succesorul in inordine)
 */
TreeNode* successor(TreeNode* x) {
	if (x == NULL)
	{
		return NULL;
	}
	if (x->right != NULL)
		return minimum(x->right);
	else
	{
		TreeNode* p1, * p2;
		p1 = x;
		p2 = x->parent;
		while (p2 != NULL && p1 == p2->right)
		{
			p1 = p2;
			p2 = p2->parent;
		}
		return p2;
	}
}
/* Functie pentru gasirea predecesorului unui nod
 * (predecesorul in inordine)
 */
TreeNode* predecessor(TreeNode* x) {
	if (x == NULL)
	{
		return NULL;
	}
	if (x->left != NULL)
		return maximum(x->left);
	else
	{
		TreeNode* p1, * p2;
		p1 = x;
		p2 = x->parent;
		while (p2 != NULL && p1 == p2->left)
		{
			p1 = p2;
			p2 = p2->parent;
		}
		return p2;
	}
}
/* Actualizeaza inaltimea unui nod din arbore
 */
void updateHeight(TreeNode* x) {
	int leftHeight = 0;
	int rightHeight = 0;
	if (x != NULL) {
		if (x->left != NULL)  leftHeight = x->left->height;
		if (x->right != NULL) rightHeight = x->right->height;
		x->height = MAX(leftHeight, rightHeight) + 1;
	}
}
/* Functie ce primeste adresa unui arbore si
 * a unui nod x si realizeaza o rotatie la stanga
 * a subarborelui care are varful in x
 *
 *   (x)	 Rotatie    (y)
 *	 / \     stanga     / \
 *  a  (y)    ---->   (x)  c
 *	   / \			  / \
 *    b   c          a   b
 */
void avlRotateLeft(TTree* tree, TreeNode* x) {
	if (tree == NULL || x == NULL) return;
	TreeNode* y = x->right;
	TreeNode* orig_parent = x->parent;
	char lr;
	int check = 0;
	int check2 = 0;
	if (tree->root == x)
	{
		check2 = 1;
	}
	if (x->parent != NULL)
	{
		check = 1;
		if (x->parent->left == x)
		{
			lr = 'l';
		}
		else
		{
			lr = 'r';
		}
	}
	x->right = y->left;
	y->left = x;
	x->parent = y;
	if (x->right != NULL) x->right->parent = x;
	y->parent = orig_parent;
	if (check == 1)
	{
		if (lr == 'l')
		{
			orig_parent->left = y;
		}
		else
		{
			orig_parent->right = y;
		}
	}
	if (check2 == 1)
	{
		tree->root = y;
	}
	updateHeight(x);
	updateHeight(y);
}
/* Functie ce primeste adresa unui arbore si
 * a unui nod x si realizeaza o rotatie la dreapta
 * a subarborelui care are varful in y
 *
 *     (y)	 Rotatie    (x)
 *	   / \   dreapta    / \
 *   (x)  c   ---->    a  (y)
 *	 / \			      / \
 *  a   b                b   c
 */
void avlRotateRight(TTree* tree, TreeNode* y) {
	if (tree == NULL || y == NULL) return;
	TreeNode* x = y->left;
	TreeNode* orig_parent = y->parent;
	char lr;
	int check = 0;
	int check2 = 0;
	if (tree->root == y)
	{
		check2 = 1;
	}
	if (y->parent != NULL)
	{
		check = 1;
		if (y->parent->left == y)
		{
			lr = 'l';
		}
		else
		{
			lr = 'r';
		}
	}
	y->left = x->right;
	x->right = y;
	y->parent = x;
	if (y->left != NULL) y->left->parent = y;
	x->parent = orig_parent;
	if (check == 1)
	{
		if (lr == 'l')
		{
			orig_parent->left = x;
		}
		else
		{
			orig_parent->right = x;
		}
	}
	if (check2 == 1)
	{
		tree->root = x;
	}
	updateHeight(x);
	updateHeight(y);
}
/* Calculeaza factorul de echilibrare pentru un nod x
 * (AVL balance factor)
*/
int avlGetBalance(TreeNode* x) {
	int leftHeight = 0;
	int rightHeight = 0;
	if (x == NULL)
	{
		return 0;
	}
	if (x != NULL) {
		if (x->left != NULL)  leftHeight = x->left->height;
		if (x->right != NULL) rightHeight = x->right->height;
		return leftHeight - rightHeight;
	}
}
/* Functie pentru reechilibrarea unui arbore AVL
 * in urma unei inserari prin rotatii simple sau duble
 * si recalcularea inaltimii fiecarui nod intalnit parcurgand
 * arborele de jos in sus, spre radacina
 *
 */
void avlFixUp(TTree* tree, TreeNode* y) {
	TreeNode* n = y->parent;
	TreeNode* z = y;
	while (n != NULL)
	{
		updateHeight(n);
		TreeNode* x = n->parent;
		if (x != NULL)if (avlGetBalance(x) <= -2 || avlGetBalance(x) >= -2)
		{
			if (n == x->left)
			{
				if (z == x->left->left)
				{
					avlRotateRight(tree, x);
				}
				else
				{
					if (z == x->left->right)
					{
						avlRotateLeft(tree, n);
						avlRotateRight(tree, x);
					}
				}
			}
			else
			{
				if (n == x->right)
				{
					if (z == x->right->right)
					{
						avlRotateLeft(tree, x);
					}
					else
					{
						if (z == x->right->left)
						{
							avlRotateRight(tree, n);
							avlRotateLeft(tree, x);
						}
					}
				}
			}
			break;
		}
		n = n->parent;
		z = z->parent;
	}
}
/* Functie pentru crearea unui nod
 *
 * value: valoarea/cheia din cadrul arborelui
 * info: informatia/valoarea din dictionar
 */
TreeNode* createTreeNode(TTree* tree, void* value, void* info) {
	if (tree == NULL)
		return NULL;
	// Alocarea memoriei
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	// Setarea elementului si a informatiei
	node->elem = tree->createElement(value);
	node->info = tree->createInfo(info);
	// Initializarea legaturilor din cadrul arborelui
	node->parent = node->right = node->left = NULL;
	// Initializarea legaturilor din cadrul listei dublu inlantuite
	node->next = node->prev = node->end = NULL;
	// Inaltimea unui nod nou este 1
	// Inaltimea lui NULL este 0
	node->height = 1;
	return node;
}
/* Inserarea unul nou nod in cadrul multi-dictionarului
 * ! In urma adaugarii arborele trebuie sa fie echilibrat
 *
 */
void insert(TTree* tree, void* elem, void* info) {
	if (tree == NULL)
	{
		return;
	}
	TreeNode* n = createTreeNode(tree, elem, info);
	if (isEmpty(tree) == 1)
	{
		tree->root = n;
		return;
	}
	TreeNode* p = search(tree, tree->root, elem);
	if (p != NULL)
	{
		return;
	}
	TreeNode* temp = tree->root;
	TreeNode* y = NULL;
	while (temp != NULL)
	{
		y = temp;
		if (tree->compare(n, temp) <= -1)
		{
			temp = temp->left;
		}
		else
		{
			temp = temp->right;
		}
	}
	n->parent = y;
	if (y == NULL)
	{
		tree->root = n;
	}
	else
	{
		if (tree->compare(n, y) == -1)
		{
			y->left = n;
		}
		else
		{
			y->right = n;
		}
	}
}
/* Eliminarea unui nod dintr-un arbore
 *
 * ! tree trebuie folosit pentru eliberarea
 *   campurilor `elem` si `info`
 * */
void destroyTreeNode(TTree* tree, TreeNode* node) {
	// Verificarea argumentelor functiei
	if (tree == NULL || node == NULL) return;
	// Folosirea metodelor arborelui
	// pentru de-alocarea campurilor nodului
	tree->destroyElement(node->elem);
	tree->destroyInfo(node->info);
	// Eliberarea memoriei nodului
	free(node);
}
/* Eliminarea unui nod din arbore
 *
 * elem: cheia nodului ce trebuie sters
 * 	! In cazul in care exista chei duplicate
 *	  se va sterge ultimul nod din lista de duplicate
 */
void delete(TTree* tree, void* elem) {
	TreeNode* p = search(tree, tree->root, elem);
	if (p == NULL)
	{
		return;
	}
	if (p->left == NULL && p->right == NULL)
	{
		p->parent->left = NULL;
		p->parent->right = NULL;
		destroyTreeNode(tree, p);
		return;
	}
	if ((p->left == NULL && p->right != NULL) && (p->left != NULL && p->right == NULL))
	{
		if (p->left == NULL)
		{
			p->right->parent = p->parent;
			TreeNode* x = p->right;
			if (p->parent->left == p)
			{
				p->parent->left = p->right;
			}
			else
			{
				p->parent->right = p->right;
			}
			destroyTreeNode(tree, p);
			avlFixUp(tree, x);
			return;
		}
		else
		{
			p->left->parent = p->parent;
			TreeNode* x = p->left;
			if (p->parent->left == p)
			{
				p->parent->left = p->left;
			}
			else
			{
				p->parent->right = p->left;
			}
			destroyTreeNode(tree, p);
			avlFixUp(tree, x);
			return;
		}
	}
	else
	{
		insertSub(tree, p->right);
		insertSub(tree, p->left);
		destroyTreeNode(tree, p);
	}
	draw_tree(tree, 1);
}
void insertSub(TTree* tree, TreeNode* p)
{
	insert(tree, p->elem, p->info);
	if (p->right != NULL)
	{
		insertSub(tree, p->right);
	}
	if (p->left != NULL)
	{
		insertSub(tree, p->left);
	}
}
/* Eliberarea memoriei unui arbore
 */
void destroyTree(TTree* tree) {
	/* Se poate folosi lista dublu intalntuita
	 * pentru eliberarea memoriei
	 */
	if (tree == NULL || tree->root == NULL)
		return;
	TreeNode* p = minimum(tree->root);
	deleteNode(tree, p);
}
void deleteNode(TTree* tree, TreeNode* p)
{
	if (p == NULL)
	{
		return;
	}
	do
	{
		TreeNode* prev = p->next;
		p = p->next;
		destroyTreeNode(tree, prev);
	} while (p != NULL);
}