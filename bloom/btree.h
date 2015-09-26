typedef struct btree_node_ {
  struct btree_node_* left;
  struct btree_node_* right;
  struct btree_node_* parent;
  char color;
  char* value;
} btree_node;

typedef struct {
  btree_node* top;
} btree;

typedef char bool;

btree* btree_init();
btree_node* btree_add(btree*, char* value);
bool btree_contains(btree*, char* value);
void btree_free(btree*);
void btree_node_free(btree_node*);
void btree_balancing(btree*, btree_node*);
void btree_node_left_rotation(btree*, btree_node*);
void btree_node_right_rotation(btree*, btree_node*);
void btree_print(btree*);
