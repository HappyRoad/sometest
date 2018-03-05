#include<iostream>
using namespace std;

typedef struct BNode {
	int data;
	BNode *lchild, *rchild;
}*BTree;

BNode* init_node(int data) {
	BNode *p = new(BNode);
	p->data = data;
	p->lchild = NULL;
	p->rchild = NULL;
	return p;
}

bool search(BTree t, int key, BNode *pre, BNode* &n) {
	if (!t){
		n = pre;
		return false;
	}else if (t->data == key) {
		n = t;
		return true;
	}else if(t->data > key) {
		return search(t->lchild, key, t, n);
	}else{
		return search(t->rchild, key, t, n);
	}
}

bool insert(BTree &t, int key) {
	BNode * data = init_node(key);
	if (!t) {
		t = data;
		return true;
	}
	BNode *p;
	if(search(t, key, NULL, p)){
		return false;
	}
	if(p->data > key){
		p->lchild = data;
	}else{
		p->rchild = data;
	}
	return true;
}

// 中序遍历
void print(BTree t){
	if(!t)return;

	print(t->lchild);
	cout << t->data << " ";
	print(t->rchild);
}

BTree init_btree(int e[], int len){
	BTree t;
	for(int i=0; i<len; i++){
		insert(t, e[i]);
		cout << e[i] << " ";
	}
	cout << endl;
	return t;
}

//右继方式
bool remove(BTree &t, int key, bool r) {
	BNode *s;
	BNode *p;
	if (!t)return true;
	if (t->data == key){
		if (t->lchild == NULL){ //左子树为空
			s = t;
			t = t->rchild;
			free(s);
		}else if(t->rchild == NULL){//右子树为空
			s = t;
			t = t->lchild;
			free(s);
		}else if (r) {//左右子树都存在, 右继方式
			s = t;
			p = t->rchild;
			while(p->lchild){
				s = p;
				p = p->lchild;
			}
			t->data = p->data;
			if(s == t){ // 右子树无左节点
				t->rchild = p->rchild;
			}else{
				s->lchild = p->rchild;
			}
			free(p);
		}else{ //左继方式
			s = t;
			p = t->lchild;
			while(p->rchild){
				s = p;
				p = p->rchild;
			}
			t->data = p->data;
			if(s == t){
				t->lchild = p->lchild;
			}else{
				s->rchild = p->lchild;
			}
			free(p);
		}
	}else if (t->data < key){
		return remove(t->rchild, key, r);	
	}else{
		return remove(t->lchild, key, r);
	}
	return true;
}

int main(int argc, char * argv[]){
	int e[] = {20, 5, 21, 3, 8, 9, 6, 7};
	BTree t = init_btree(e, sizeof(e)/sizeof(int));
	BNode *p;
	if (search(t, 1, NULL, p)) {
		cout << "found 1" << endl;
	}else{
		cout << "not found 1" << endl;
	}
	if (search(t, 4, NULL, p)) {
		cout << "found 4" << endl;
	}else{
		cout << "not found 4" << endl;
	}
	if (insert(t, 3)){
		cout << "insert 3 ok" << endl;	
	}else{
		cout << "insert 3 fail" << endl;
	}
	print(t);
	cout << endl;
	cout << insert(t, 8) << endl;
	print(t);
	cout << endl;
	cout << insert(t, 10) << endl;
	print(t);
	cout << endl;
	cout << remove(t, 5, true) << endl;
	print(t);
	cout << endl;
	return 1;
}
