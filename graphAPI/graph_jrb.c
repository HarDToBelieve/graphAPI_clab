#include "graph_jrb.h"
#include <stdlib.h>

Graph createGraph() {
	return make_jrb();
}

void addEdge(Graph G, int v1, int v2) {
	Graph v1_find = jrb_find_int (G, v1);
	Graph v2_find = jrb_find_int (G, v2);
	Graph tree_v1, tree_v2;

	if ( v1_find == NULL && v2_find == NULL ) {
		tree_v1 = make_jrb();
		tree_v2 = make_jrb();
		jrb_insert_int (G, v1, new_jval_v(tree_v1));
		jrb_insert_int (G, v2, new_jval_v(tree_v2));
	}
	else if ( v2_find == NULL ) {
		Graph node = jrb_find_int (G, v1);
		tree_v1 = (Graph) jval_v(node->val);
		tree_v2 = make_jrb();
		jrb_insert_int (G, v2, new_jval_v(tree_v2));
	}
	else if ( v1_find == NULL ) {
		Graph node = jrb_find_int (G, v2);
		tree_v2 = (Graph) jval_v(node->val);
		tree_v1 = make_jrb();
		jrb_insert_int (G, v1, new_jval_v(tree_v1));
	}
	else {
		Graph node_v1 = jrb_find_int (G, v1);
		tree_v1 = (Graph) jval_v(node_v1->val);
		Graph node_v2 = jrb_find_int (G, v2);
		tree_v2 = (Graph) jval_v(node_v2->val);
	}
	jrb_insert_int (tree_v1, v2, new_jval_i(1));
	jrb_insert_int (tree_v2, v1, new_jval_i(1));
}

int adjacent(Graph G, int v1, int v2) {
	Graph node = jrb_find_int(G, v1);
	if ( node == NULL ) {
		puts ("Cannot find vertex");
		return;
	}
	Graph tree = (Graph) jval_v(node->val);
	jrb_traverse(node, tree)
		if ( jval_i(node->key) == v2 ) 
			return true;
	return false;
}

int getAdjacentVertices(Graph G, int v, int* output) {
	Graph node = jrb_find_int (G, v);
	if ( node == NULL ) {
		puts ("Cannot find vertex");
		return;
	}
	Graph tree = (Graph) jval_v(node->val);
	int total = 0;
	jrb_traverse(node, tree)
		output[total++] = jval_i(node->key);

	return total;
}

void dropGraph(Graph G) {
	Graph node;
	jrb_traverse(node, G)
		jrb_free_tree(jval_v(node->val));
}

int getNumofV(Graph G) {
	int cnt = 0;
	Graph node;
	jrb_traverse(node, G)
		cnt ++;
	return cnt;
}

void bfs (Graph G, int start, int stop, void (*func)(int)) {
	int V = getNumofV(G);
	JRB visited = make_jrb();
	Dllist node;
	int i;

	Dllist queue = new_dllist();
	dll_append(queue, new_jval_i(start));
	jrb_insert_int(visited, start, new_jval_i(1));

	while ( !dll_empty(queue) ) {
		node = dll_first(queue);
		int u = jval_i(node->val);
		dll_delete_node(node);

		(*func)(u);
		if ( u == stop ) return;
		int *output = (int*)malloc(V);
		int num = getAdjacentVertices(G, u, output);

		for (i=0; i<num; ++i) {
			int v = output[i];
			Graph v_find = jrb_find_int(visited, v);
			if ( v_find == NULL ) {
				jrb_insert_int(visited, v, new_jval_i(1));
				dll_append(queue, new_jval_i(v));
			}
		}	
	}
}

void dfs (Graph G, int start, int stop, void (*func)(int)) {
	int V = getNumofV(G);
	JRB visited = make_jrb();
	Dllist node;
	int i;

	Dllist stack = new_dllist();
	dll_append(stack, new_jval_i(start));
	jrb_insert_int(visited, start, new_jval_i(1));

	while ( !dll_empty(stack) ) {
		node = dll_last(stack);
		int u = jval_i(node->val);
		dll_delete_node(node);

		(*func)(u);
		if ( u == stop ) return;
		int *output = (int*)malloc(V);
		int num = getAdjacentVertices(G, u, output);

		for (i=0; i<num; ++i) {
			int v = output[i];
			Graph v_find = jrb_find_int(visited, v);
			if ( v_find == NULL ) {
				jrb_insert_int(visited, v, new_jval_i(1));
				dll_append(stack, new_jval_i(v));
			}
		}
	}
}