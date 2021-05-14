#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include "queue.h"
#include "graph.h"
#include "dlist.h"

#define MAXCHAR 1000

graph *BreadthFirst(graph *g, node *n)
{
  queue *q = queue_empty(NULL);
  graph_node_set_seen(g, n, true); // (n,g)←seen(n,g) , mark the node as seen.
  queue_enqueue(q,n); // Put node in queue.
  while (!queue_is_empty(q))
  {
    struct node *p = queue_front(q); // Pick first node from queue
    queue_dequeue(q); //Remove the first element from the queue
    struct dlist *neighbours=graph_neighbours(g,p);

    dlist_pos pos = dlist_first(neighbours);
    while(!dlist_is_empty(neighbours))
    {
      struct node *m = dlist_inspect(neighbours, pos);
      if (!graph_node_is_seen(g, m))
      {
        g=graph_node_set_seen(g, m, true);
        q = queue_enqueue(q,m);
      }
    }
  }
  return g;
}

bool dest_found(graph *g, node *n2)
{
  return graph_node_is_seen(g, n2);
}

bool find_path(graph *g, node *src, node *dest)
{
  //travsering the graph
  g=BreadthFirst(g,src);

  //return if the destination have been marked as seen
  return dest_found(g, dest);
}



int main(void) {
  graph *g = graph_empty(1000);

  graph_insert_node(g, "A");
  graph_insert_node(g, "B");
  graph_insert_node(g, "C");
  graph_insert_node(g, "D");
  graph_insert_node(g, "E");
  graph_insert_node(g, "F");

  struct node *A = graph_find_node(g,"A");
  struct node *B = graph_find_node(g,"B");
  struct node *C = graph_find_node(g,"C");
  struct node *D = graph_find_node(g,"D");
  struct node *E = graph_find_node(g,"E");
  struct node *F = graph_find_node(g,"F");
  graph_insert_edge(g, A, B);
  graph_insert_edge(g, A, C);
  graph_insert_edge(g, C, D);
  graph_insert_edge(g, B, C);
  graph_insert_edge(g, D, A);
  graph_insert_edge(g, E, F);
  struct node *src = A;
  struct node *dest = B;


  if (src == dest || find_path(g, src, dest) )
  {
    printf("There is a path");
    //printf("There is a path from %s to %s.\n", src->name, dest->name);
  }
  else
  {
    printf("There is no path");
  }
    printf("Normal exit.\n");

    //reset seen status between runs:
    g=graph_reset_seen(g);

    printf("Normal exit.\n");
    return 0;
}
//Finns slide 38/104 bredden-först-travisering, sida 110
//Check if destination and source is seen.
//Graph reset: Use graph_reset_seen
