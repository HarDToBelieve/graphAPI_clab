#include "graph_jrb.h"
#include <stdlib.h>
#include <string.h>

Graph createGraph() {
	return make_jrb();
}

void addEdge (Graph G, char *mapping[], char *name1, char *name2, int mode) {
	int v1 = addVertex (G, mapping, name1);
	int v2 = addVertex (G, mapping, name2);

	Graph tree_v1, tree_v2;

	Graph node_v1 = jrb_find_int (G, v1);
	tree_v1 = (Graph) jval_v(node_v1->val);
	Graph node_v2 = jrb_find_int (G, v2);
	tree_v2 = (Graph) jval_v(node_v2->val);
	
	jrb_insert_int (tree_v1, v2, new_jval_i(1));
	if ( mode == UNDIRECTED )
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

void dfs_norecur (Graph G, int start, int stop, void (*func)(int)) {
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

int shortest_noWeight_path(Graph G, int start, int stop, int *path) {
	int V = getNumofV(G);
	Graph dist = make_jrb();
	Graph visited = make_jrb();
	Dllist node;
	int i;

	Dllist queue = new_dllist();
	dll_append(queue, new_jval_i(start));

	Graph trace = make_jrb();
	jrb_insert_int(trace, start, new_jval_i(1));
	jrb_insert_int(dist, start, new_jval_v(trace));
	jrb_insert_int(visited, start, new_jval_i(1));

	while ( !dll_empty(queue) ) {
		node = dll_first(queue);
		int u = jval_i(node->val);
		dll_delete_node(node);

		if ( u == stop ) {
			Graph u_find_path = jrb_find_int(dist, u);
			Graph result = jval_v(u_find_path->val);
			int shortest_path = getNumofV(result); 
			if ( path != NULL ) {
				int cnt=0;
				Graph tmp;
				jrb_traverse(tmp, result)
					path[cnt++] = jval_i(tmp->key);
			}
			return shortest_path;
		}
		int *output = (int*)malloc(V);
		int num = getAdjacentVertices(G, u, output);
		Graph u_find_path = jval_v(jrb_find_int(dist, u)->val);

		for (i=0; i<num; ++i) {
			int v = output[i];
			Graph v_find = jrb_find_int(visited, v);
			if ( v_find == NULL ) {
				jrb_insert_int(visited, v, new_jval_i(1));
				Graph current_path = make_jrb();
				Graph node;
				jrb_traverse(node, u_find_path)
					jrb_insert_int(current_path, jval_i(node->key), new_jval_i(1));

				jrb_insert_int(current_path, v, new_jval_i(1));
				jrb_insert_int(dist, v, new_jval_v(current_path));
				dll_append(queue, new_jval_i(v));
			}
		}	
	}
}

int addVertex (Graph G, char *mapping[], char *name) {
	int v = -1, i, V = getNumofV(G);
	for (i=0; i<V; ++i)
		if ( !strcmp(mapping[i], name) ) {
			v = i;
			break;
		}
	if ( v == -1 ) {
		Graph tree_v = make_jrb();
		jrb_insert_int (G, V, new_jval_v(tree_v));
		mapping [V] = (char *)malloc(strlen(name));
		strcpy (mapping[V], name);
		v = V;
	}
	return v;
}

char *getVertex (Graph G, char *mapping[], int pos) {
	return mapping[pos];
}

int indegree (Graph G, int u, int* output) {
	int i, total = 0, V = getNumofV(G);
	for (i=0; i<V; ++i)
		if ( u != i && adjacent(G, i, u) )
			output[total++] = u;
	return total;
}

int outdegree (Graph G, int u, int* output) {
	int i, total = 0, V = getNumofV (G);
	for (i=0; i<V; ++i)
		if ( u != i & adjacent(G, u, i) )
			output[total++] = u;
	return total;
}

int dfs_recur (Graph G, int u, int* visited) {
	int i, V = getNumofV(G);
	int *output = (int*)malloc(V);
	int num = getAdjacentVertices(G, u, output);
	visited[u] = 1;

	for (i=0; i<num; ++i) {
		int v = output[i];
		if ( visited[v] == 0 ) {
			if ( dfs_recur (G, v, visited) == false )
				return false;
			else continue;
		}
		else {
			return false;
		}
	}
	free (output);
	return true;
}

int DAG (Graph G) {
	int i, V = getNumofV(G);
	int *visited = (int *)malloc (V);
	for (i=0; i<V; ++i)
		visited[i] = 0;
	for (i=0; i<V; ++i)
		if ( visited[i] == 0 ) {
			if ( dfs_recur (G, i, visited) == false )
				return false;
			else continue;
		}
	free (visited);
	return true;
}