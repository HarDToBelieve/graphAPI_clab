#include "graph_jrb.h"
#include <stdlib.h>
#include <string.h>

Graph createGraph() {
	return make_jrb();
}

void addEdge (Graph G, char *mapping[], char *name1, char *name2, int weight, int mode) {
	int v1 = addVertex (G, mapping, name1);
	int v2 = addVertex (G, mapping, name2);

	Graph tree_v1, tree_v2;

	Graph node_v1 = jrb_find_int (G, v1);
	tree_v1 = (Graph) jval_v(node_v1->val);
	Graph node_v2 = jrb_find_int (G, v2);
	tree_v2 = (Graph) jval_v(node_v2->val);
	
	jrb_insert_int (tree_v1, v2, new_jval_i(weight));
	if ( mode == UNDIRECTED )
		jrb_insert_int (tree_v2, v1, new_jval_i(weight));
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

int getAdjacentVertices(Graph G, int v, JRB* output) {
	Graph node = jrb_find_int (G, v);
	if ( node == NULL ) {
		puts ("Cannot find vertex");
		return;
	}
	Graph tree = (Graph) jval_v(node->val);
	int total = 0;
	jrb_traverse(node, tree) {
		int cnt = total ++;
		if ( output != NULL )
			output[cnt] = node;
	}
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
		JRB *output = (JRB*)malloc(V * sizeof(JRB));
		int num = getAdjacentVertices(G, u, output);

		for (i=0; i<num; ++i) {
			JRB v = output[i];
			Graph v_find = jrb_find_int(visited, jval_i(v->key));
			if ( v_find == NULL ) {
				jrb_insert_int(visited, jval_i(v->key), new_jval_i(1));
				dll_append(queue, v->key);
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
		JRB *output = (JRB*)malloc(V*sizeof(JRB));
		int num = getAdjacentVertices(G, u, output);

		for (i=0; i<num; ++i) {
			JRB v = output[i];
			Graph v_find = jrb_find_int(visited, jval_i(v->key));
			if ( v_find == NULL ) {
				jrb_insert_int(visited, jval_i(v->key), new_jval_i(1));
				dll_append(stack, v->key);
			}
		}
	}
}

int shortest_noWeight_path(Graph G, int start, int stop, int *path) {
	int V = getNumofV(G);
	Graph dist = make_jrb();
	Dllist node;
	int i;

	Dllist queue = new_dllist();
	dll_append(queue, new_jval_i(start));

	Dllist trace = new_dllist();
	dll_append(trace, new_jval_i(start));
	jrb_insert_int(dist, start, new_jval_v(trace));

	while ( !dll_empty(queue) ) {
		node = dll_first(queue);
		int u = jval_i(node->val);
		dll_delete_node(node);

		Dllist u_find_path = jval_v(jrb_find_int(dist, u)->val);
		if ( u == stop ) {
			int cnt=0;
			Dllist tmp;
			dll_traverse(tmp, u_find_path) {
				cnt ++;
				if ( path != NULL )
					path[cnt-1] = jval_i(tmp->val);
			}
			return cnt;
		}
		JRB *output = (JRB*)malloc(V * sizeof(JRB));
		int num = getAdjacentVertices(G, u, output);

		for (i=0; i<num; ++i) {
			JRB v = output[i];
			Graph v_find = jrb_find_int(dist, jval_i(v->key));
			if ( v_find == NULL ) {
				Dllist current_path = new_dllist();
				Dllist node;
				dll_traverse(node, u_find_path)
					dll_append(current_path, node->val);

				dll_append(current_path, v->key);
				jrb_insert_int(dist, jval_i(v->key), new_jval_v(current_path));
				dll_append(queue, v->key);
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
		if ( u != i && adjacent(G, i, u) ) {
			int cnt = total++;
			if ( output != NULL )
				output[cnt] = u;
		}
	return total;
}

int outdegree (Graph G, int u, int* output) {
	int i, total = 0, V = getNumofV (G);
	for (i=0; i<V; ++i)
		if ( u != i & adjacent(G, u, i) ) {
			int cnt = total++;
			if ( output != NULL )
				output[cnt] = u;
		}
	return total;
}

int dfs_recur (Graph G, int start, int u, int* visited) {
	int i, V = getNumofV(G);
	JRB *output = (JRB*)malloc(V * sizeof(JRB));
	int num = getAdjacentVertices(G, u, output);
	visited[u] = 1;
	for (i=0; i<num; ++i) {
		JRB v = output[i];
		if ( jval_i(v->key) == start ) return false;
		if ( visited[jval_i(v->key)] == 0 )
			if ( dfs_recur (G, start, jval_i(v->key), visited) == false ) {
				free (output);
				return false;
			}
			else continue;
	}
	free (output);
	return true;
}

int isDAG (Graph G) {
	int i, V = getNumofV(G);
	int *visited = (int *)malloc (V*sizeof(int));
	for (i=0; i<V; ++i)
		visited[i] = 0;
	for (i=0; i<V; ++i)
		if ( visited[i] == 0 ) {
			if ( dfs_recur (G, i, i, visited) == false )
				return false;
			else continue;
		}
	free (visited);
	return true;
}

int toposort (Graph G, int *output) {
	int i, V = getNumofV (G), total = 0;
	Dllist node, queue = new_dllist ();
	int *indeg = (int*) malloc (V * sizeof(int));
	
	for (i=0; i<V; ++i) {
		indeg[i] = indegree (G, i, NULL);
		if ( indeg[i] == 0 ) dll_append (queue, new_jval_i(i));
	}
	while ( !dll_empty(queue) ) {
		node = dll_first (queue);
		int u = jval_i (node->val);
		dll_delete_node (node);

		output[total++] = u;
		JRB *adj = (JRB*)malloc (V *sizeof(JRB));
		int num = getAdjacentVertices(G, u, adj);

		for (i=0; i<num; ++i) {
			JRB v = adj[i];
			indeg[jval_i(v->key)] --;
			if ( indeg[jval_i(v->key)] == 0 )
				dll_append (queue, v->key);
		}
	}
	return total;
}

int dijkstra (Graph G, int start, int stop, int *path, int *numVertices) {
	int i, V = getNumofV(G);
	Graph trace = make_jrb(), node;
	int *cost = (int *)malloc (V * sizeof(int));
	for (i=0; i<V; ++i)
		cost[i] = INT_MAX;

	Graph pqueue = make_jrb();
	jrb_insert_int(pqueue, 0, new_jval_i(start));
	cost[start] = 0;

	Dllist tmp = new_dllist();
	dll_append(tmp, new_jval_i(start));
	jrb_insert_int(trace, start, new_jval_v(tmp));

	while ( !jrb_empty(pqueue) ) {
		node = jrb_first(pqueue);
		int u = jval_i(node->val);
		jrb_delete_node(node);

		Dllist u_find_path = jval_v(jrb_find_int(trace, u)->val);
		if ( u == stop ) {
			int cnt=0;
			Dllist tmp;
			dll_traverse(tmp, u_find_path) {
				cnt ++;
				if ( path != NULL )
					path[cnt-1] = jval_i(tmp->val);
			}
			*numVertices = cnt;
			return cost[u];
		}
		JRB *output = (JRB*)malloc(V * sizeof(JRB));
		int num = getAdjacentVertices(G, u, output);
		
		for (i=0; i<num; ++i) {
			JRB v = output[i];
			if ( cost[jval_i(v->key)] > cost[u] + jval_i(v->val) ) {
				cost[jval_i(v->key)] = cost[u] + jval_i(v->val);
				JRB old_path = jrb_find_int (trace, jval_i(v->key));
				if ( old_path != NULL )
					jrb_delete_node (old_path);
				Dllist current_path = new_dllist();
				Dllist node;
				dll_traverse(node, u_find_path)
					dll_append(current_path, node->val);

				dll_append(current_path, v->key);
				jrb_insert_int(trace, jval_i(v->key), new_jval_v(current_path));
				jrb_insert_int(pqueue, cost[u] + jval_i(v->val), v->key);
			}
		}	
	}
}

void mat2adjl (Graph G, char *mapping[], int *matrix[], int N, int mode) {
	int i, j;
	for (i=0; i<N; ++i)
		for (j=0; j<N; ++j)
			if ( matrix[i][j] != 0 ) {
				char *name1 = getVertex(G, mapping, i);
				char *name2 = getVertex(G, mapping, j);
				addEdge (G, mapping, name1, name2, matrix[i][j], mode);
				if ( mode == UNDIRECTED ) matrix[j][i] = 0;
			}
}
