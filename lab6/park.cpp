#include <iostream>
using namespace std;

const int SIZE = 500001;
const int LOG = 20;
int n, m;

struct Node {
	int value;
	int depth;
	Node* left;
	Node* right;
	Node* parent;	
};

Node* Tree[SIZE];
int queries[SIZE][2];
int links[LOG][SIZE];
// furthest node / distance to this node
int far[SIZE][2];
int fardown[SIZE][2];
int farup[SIZE][2];

void input() {
	cin >> n;
	int l, p;
	
	for (int i = 1; i <= n; i++)
		Tree[i] = new Node;
	
	for (int i = 1; i <= n; i++) {
		Tree[i]->value = i;
		cin >> l >> p;
		if (l != -1)
			Tree[i]->left = Tree[l];
		if(p != -1)
			Tree[i]->right = Tree[p];		
	}
	
	cin >> m;
	
	for (int i = 1; i <= m; i++)
		cin >> queries[i][0] >> queries[i][1];
}

void init_tree(Node* node, int d) {
	
	node->depth = d;
			
	if (node->left != NULL) {
		init_tree(node->left, d + 1);
		node->left->parent = node;
	}
	
	if (node->right != NULL) {
		init_tree(node->right, d + 1);
		node->right->parent = node;
	}
		
}

void init_links() {
	
	links[0][1] = -1;
	
	for (int j = 2; j <= n; j++)
		links[0][j] = Tree[j]->parent->value;
	
	for (int i = 1; i < LOG; i++)
		for (int j = 1; j <= n; j++)
			if (links[i - 1][j] == -1)
				links[i][j] = -1;
			else
				links[i][j] = links[i - 1][links[i - 1][j]];
				
}

/**
 * Highest power of 2 that not exceeds num
 */
int pot(int num) {
	int res = 1;
	while (num) {
		num >>= 1;
		res <<= 1;
	}
	
	return res >> 1;
}


/**
 * Floor logarithm
 */
 int log(int num) {
	 int res = 0;
	 while (num) {
		 num >>= 1;
		 res++;
	 }
	 
	 return res - 1;
 }

/** 
 * node that lies upper within a distance h
 */
Node* ancestor(Node* node, int h) {
	int res = node->value;
	int power = pot(h);
	
	while (h > 0 && res != -1) {
		if (power > h)
			power >>= 1;
		else {
			res = links[log(h)][res];
			h -= power;
		}
	}
	
	return Tree[res];
}

/**
 * Find the lowest common ancestor of two nodes. (LCA)
 */
Node* lca(Node* node1, Node* node2) {
	
	int d1 = node1->depth, d2 = node2->depth;
	
	if (d1 < d2)
		node2 = ancestor(node2, d2 - d1);
	else if (d2 < d1)
		node1 = ancestor(node1, d1 - d2);
	
	if (node1 == node2)
		return node1;
		
	int i = log(n);
	
	while (i >= 0) {
		if(links[i][node1->value] != links[i][node2->value]) {
			node1 = Tree[links[i][node1->value]];
			node2 = Tree[links[i][node2->value]];
		}		
		
		i--;
		
	}
	
	return node1->parent;
	
}

/**
 * wrapper for lca
 */
 int lca(int n1, int n2) {
	 return lca(Tree[n1], Tree[n2])->value;
 }

/**
 * find the most distant node (and distance to it) in the subtree
 */
void count_fardown(Node* node) {
	int val = node->value;
	fardown[val][0] = val;
	fardown[val][1] = -1;
	
	
	if (node->left != NULL) {
		count_fardown(node->left);
	}
		
	if (node->right != NULL) {
		count_fardown(node->right);
	}
	
	if (node->left != NULL && fardown[node->left->value][1] > fardown[val][1]) {
		fardown[val][0] = fardown[node->left->value][0];
		fardown[val][1] = fardown[node->left->value][1];
	}
	
	if (node->right != NULL && fardown[node->right->value][1] > fardown[val][1]) {
		fardown[val][0] = fardown[node->right->value][0];
		fardown[val][1] = fardown[node->right->value][1];
	}
	
	fardown[val][1]++;
}

Node* sibling(Node* node) {
	if(node == NULL)
		return NULL;
		
	Node* par = node->parent;
	if (par == NULL)
		return NULL;
	
	if (par->left == node)
		return par->right;
	else
		return par->left;
	
}

/**
 * find the most distant node on the way up.
 */
 void count_farup(Node* node) {
	 int val = node->value;
	 farup[val][0] = val;
	 farup[val][1] = 0;
	 
	 if (node->parent != NULL) {
		 int d = farup[node->parent->value][1];
		 if (d + 1 > farup[val][1]) {
			farup[val][0] = farup[node->parent->value][0];
			farup[val][1] = d + 1; 
		}
	 }
	 
	 Node* sib = sibling(node);
	 if (sib != NULL) {
		 int d = fardown[sib->value][1];
		 if (d + 2 > farup[val][1]) {
			farup[val][0] = fardown[sib->value][0];
			farup[val][1] = d + 2;
		 }
	}
	 
	 
	if (node->left != NULL)
		count_farup(node->left);
	
	if (node->right != NULL)
		count_farup(node->right);
	
 }

/**
 * for each node find the furthest one from it and the distance to it.
 */
void count_furthest() {
	// count fardown
	count_fardown(Tree[1]);
		
	// count farup
	count_farup(Tree[1]);
	
	
	// final stage
	for (int i = 1; i <= n; i++) {
		if (fardown[i][1] > farup[i][1]) {
			far[i][0] = fardown[i][0];
			far[i][1] = fardown[i][1];
		}
		else {
			far[i][0] = farup[i][0];
			far[i][1] = farup[i][1];
		}
	}
}

int answer_query(Node* node, int dist) {
	Node* farthest = Tree[far[node->value][0]];
	int dist_to_farthest = far[node->value][1];
	if (dist > dist_to_farthest)
		return -1;
	
	Node* lca_node = lca(node, farthest);
	
	int d1 = node->depth - lca_node->depth;
	
	if (dist <= d1)
		return ancestor(node, dist)->value;
	else
		return ancestor(farthest, dist_to_farthest - dist)->value;
	
}


void answer_queries() {
	for (int i = 1; i <= m; i++)
		cout << answer_query(Tree[queries[i][0]], queries[i][1]) << endl;
}


int main() {
	
	input(); 
	init_tree(Tree[1], 0);
	init_links();
	count_furthest();
	answer_queries();
	
	return 0;	
}
