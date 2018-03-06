#include <cstdio>
#include <iostream>
#include <cmath>

#define YES true
#define NO false
#define NEGINF 0x80000000
#define POSINF 0x7FFFFFFF
/* not necessarily infinities, but who cares at this point, we have here
more curious thing, that is me being so annoyed with Objective-C I actually
consciously defined true and false as yes and no. I really need help here.*/


class Fib_Heap{ //why Fibonacci's heap
public:
	struct node{
		int key;
		node* parent = NULL;
		node* child = NULL;
		node* left = this;
		node* right = this;
		int degree = 0;
		int mark = NO;

		int index;
	};
	node* min;
	int n;
	node* rootlist;
	node** A;
	bool ascend;

	Fib_Heap(bool is){
		min = NULL;
		n = 0;
		ascend = is;
	};

	~Fib_Heap(){
		min = NULL;
		rootlist = NULL;
		delete &n;
		delete min;
		delete rootlist;
		delete &ascend;
	}

	node* retMin(Fib_Heap *kop){	//return max/min valuse
		return kop->min;
	}

	bool order_cmp(int a, int b){	//compare values, depending on sorting order
		if (ascend == YES){	return a < b;}
		else{ return a > b; }
	}

	void insNode(node* x){ //insert
		/*x->degree = 0;
		x->parent = NULL;
		x->left = x;
		x->right = x;
		x->child = NULL;
		x->mark = NO;*/
		if (this->rootlist == NULL){ this->rootlist = x; }
		else { toTheList(x, this->rootlist); }
		if (this->min == NULL || order_cmp( x->key,  this->min->key)){
			this->min = x;
		}
		this->n++;
	}

	void toTheList(node* x, node* r){  //add to list
		if (r == NULL) r = x;
		else{
			x->right = r->right;
			x->left = r;
			r->right->left = x;
			r->right = x;
		}
	}

	Fib_Heap* stickTwo(Fib_Heap* itchy, Fib_Heap* doze){ //union
		Fib_Heap* H = new Fib_Heap(itchy->ascend);
		H->min = itchy->min;
		listMerge(itchy->rootlist, doze->rootlist);
		if (itchy->min == NULL ||
			(doze->min != NULL &&
			doze->min < itchy->min)){
			H->min = doze->min;
		}
		H->n = itchy->n + doze->n;
		delete itchy;
		delete doze;
		return H;
	}
	
	void listMerge(node*a, node* b){	//merge lists
		node *temper = a->right;
		a->right->left = b->left;
		a->right = b;
		b->left->right = temper;
		b->left = a;
	}

	void linkThings(node* x, node* y){	//link
		outOfTheList(y);
		toTheList(y, x->child);
		x->degree++;
		y->mark = NO;
	}

	void outOfTheList(node* x){		//removal from list
		x->left->right = x->right;
		x->right->left = x->left;
	}

	void nodeSwap(node* x, node* y){	//node swap
		node* temp = x;
		x = y;
		y = temp;
	}

	void consoSomething(){		//consolidate
		int a = (int)log2(this->n) + 1;
		node *x, *y;
		int d;
		this->A = new node*[a];
		for (int i = 0; i < a; i++){ this->A[i] = NULL; }
		for (node* w = this->rootlist->right; w != rootlist; w = w->right){
			x = w;
			d = x->degree;
			while (A[d] != NULL){
				if (A[d] == NULL || d >= a){ break; }
				y = A[d];
				if (order_cmp(x->key , y->key)){ nodeSwap(x, y); }
				this->linkThings(x, y);
				A[d] = NULL;
				d++;
			}
			A[d] = x;
			if (w->right = w){ break; }
		}
		this->min = NULL;
		for (int i = 0; i < a; i++){
			if (A[i] != NULL){
				toTheList(A[i], this->rootlist);
				if (this->min == NULL || order_cmp( A[i]->key, this->min->key)){ this->min = A[i]; }
			}
		}
		delete[] this->A;
	}

	node* getMinOut(){	//extract min/max
		node* z = this->min, *zr;
		if (z != NULL){
			if (z->child != NULL){
				for (node* i = z->child->right; i != z->child; i = z->child->right){
					i->parent = NULL;
					toTheList(i, this->rootlist);
				}
			}
			zr = z->right;
			outOfTheList(z);
			if (z == zr){ this->min = NULL; }
			else{
				this->min = zr;
				this->consoSomething();
			}
			this->n--;
		}
		return z;
	}

	void keySubstract(node* x, int k){	//de/increase key value
		//if (order_cmp(k, x->key)){
			node* y = x->parent;
			x->key = k;
			if (y != NULL && order_cmp(x->key, y->key)){
				HM01(x, y);
				Casca01(y);
			}
			if (order_cmp(x->key , this->min->key)){ this->min = x; }
		//}
	
	}

	void HM01(node* x, node* y){	//cut
		outOfTheList(x);
		y->degree--;
		toTheList(x, this->rootlist);
		x->parent = NULL;
		x->mark = NO;
	}

	void Casca01(node *y){	//cascading cut
		node* z = y->parent;
		if (z != NULL){
			if (y->mark == NO){	y->mark = YES;	}
			else{
				HM01(y, z);
				Casca01(z);
			}
		}
	}

	node* deltree(node* x){	//delete a node
		if (this->ascend == YES){ keySubstract(x, NEGINF); }
		else{ keySubstract(x, POSINF); }
		return getMinOut();
	}

	void keyAttract(node* x, int k){ //the opposite thing to keySubstract, but more complex
		node* temp = deltree(x);
		temp->key = k;
		insNode(x);
	}
};


struct tab2point{
	int value;
	Fib_Heap::node* maxPointer;
	Fib_Heap::node* minPointer;

};



int main(){
	int ele, instr;
	Fib_Heap *Min = new Fib_Heap(YES),
		*Max = new Fib_Heap(NO);
	Fib_Heap::node *temp;
	char cmd[2];
	int rauz, dua;

	//scanf("%d %d", &ele, &instr);
	std::cin >> ele >> instr;
	tab2point* elvader = new tab2point[ele];
	
	for (int i = 0; i < ele; i++){
		//scanf("%d", elvader[i].value);
		std::cin >> elvader[i].value;
		temp = new Fib_Heap::node;
		if (elvader[i].value != 0){	temp->key = elvader[i].value;}
		else { temp->key = POSINF; }
		temp->index = i;
		Min->insNode(temp);
		elvader[i].minPointer = temp;

		temp = new Fib_Heap::node;
		temp->key = elvader[i].value;
		temp->index = i;
		Max->insNode(temp);
		elvader[i].maxPointer = temp;
	}
	for (int inst = 0; inst < instr; inst++){
		cmd[0] = cmd[1] = ' ';
		//scanf("%2s %[^\n]%d", cmd, &rauz, &dua);
		std::cin >> cmd;
		if (std::cin && std::cin.peek() != '\n'){std::cin >> rauz;
			if (std::cin && std::cin.peek() != '\n'){std::cin >> dua;}
		}


		switch (cmd[0]){
		case 'r':
			if (cmd[1] == 'm'){ dua = rauz; rauz = Min->min->index; }
			if (cmd[1] == 'M'){ dua = rauz; rauz = Max->min->index; }

			if (elvader[rauz].value - dua > 0){
				elvader[rauz].value -= dua;
				Min->keySubstract(elvader[rauz].minPointer, elvader[rauz].value - dua);
				Max->keyAttract(elvader[rauz].maxPointer, elvader[rauz].value - dua);
			}
			else{
				elvader[rauz].value = 0;
				Min->keyAttract(elvader[rauz].minPointer, POSINF);
				Max->keyAttract(elvader[rauz].maxPointer, 0);
			}
			break;
		case 'w':
			if (cmd[1] == ' '){	std::cout << elvader[rauz].value <<std::endl;}
			if (cmd[1] == 'm'){
				if(Min->min->key != POSINF) std::cout << Min->min << std::endl;
				else std::cout << 0 << std::endl;
			}
			if (cmd[1] == 'M'){ std::cout << Max->min << std::endl; }
			break;
		case'n':
			if (cmd[1] == 'm'){ dua = rauz; rauz = Min->min->index; }
			if (cmd[1] == 'M'){ dua = rauz; rauz = Max->min->index; }

			Min->keyAttract(elvader[rauz].minPointer, elvader[rauz].value + dua);
			Max->keySubstract(elvader[rauz].minPointer, elvader[rauz].value + dua);
			break;
		
		
		}


	}

	return 0;
}