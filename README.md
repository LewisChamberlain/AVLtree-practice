This is a AVLtree practice project, includes defining AVL structure, set up new AVLtree,insertion and deletion.Properties of AVLtree:1.left and right subtrees of any node matain a height (depth) difference which is no more than 1. 
insertion of AVLtree: resemble to BST, find the location for inserting, than traversing from leaf to root and find the first unbalanced subtree (has a height difference larger than 1), than adjust the subtree. Assuming this subtree is tree x, and inserting node i lead to the tree x’s unbalance, regarding four different occasions, there are four different adjustments. 
First, if i is in the left sub of x’s left child, call it case LL, right rotate the left child to replace x’s root, former root becomes the right child of new root, and the former right child of new root becomes former root’s left child.
Second, if i is in the right sub of x’s right child, it is case RR, left rotate the right child to replace x’s root, former root becomes the left child of new root, the former left child of new root becomes former root’s right child.
Third, for LR case, left rotate the right child of root’s left child and replace root’s left child, than right rotate the new left child to replace root, original left child of the final root becomes the right sub of the original root’s left child, the original right child of the final root becomes the left sub of original root.
Finally, considering RL case, right rotate the child left of root’s right child and replace root’s right child, then left rotate it to replace the root, original right child of the final root becomes the left sub of the original root’s right child, the original left child of the final root becomes the right sub of the original root.
Deletion: the same way to find target node as searching in a BST, than find the unbalanced subtree as you did when insert, after that, find the highest first-generation subtree of the unbalanced subtree and the highest second-generation of that high first generation subtree that you found, the relative direction from the original unbalanced subtree’s root to this second-generation subtree’s root determines which case it belongs to (LL, RR, LR or RL), adjust the subtree by the same way of insertion.
这是一个平衡二叉树实践项目，包括定义平衡二叉树结构，建立新的平衡二叉树，插入和删除。平衡二叉树的属性:任意节点的左右子树保持高度(深度)差不大于1。

平衡二叉树的插入:类似于二叉查找树，找到插入的位置，然后从叶子遍历到根，找到第一个不平衡的子树(高度差大于1)，然后调整子树。假设这个子树是树x，插入节点i导致树x不平衡，针对四种不同的情况，进行四种不同的调整。

首先，如果i在x左子结点的左子结点中，则为LL型，右旋左子结点来替换x的根结点，前根结点成为新根结点的右子结点，新根结点的前右子结点成为前根结点的左子结点。

第二，如果i在x的右子结点的右子结点中，RR，左旋右子结点来替换x的根结点，前根结点成为新根结点的左子结点，新根结点的前左子结点成为前根结点的右子结点。

第三，对于LR，左旋根的左子的右子并替换根的左子节点，然后右旋新的左子来替换最初的根，最终的根的原左子节点成为原根的左子节点的右子节点，最终的根的原右子节点成为原初根的左子节点的左子节点。

最后，RL情况，右旋根的右子节点的左子节点并替换最初的根的右子节点，然后左旋转它来替换初根，最终的根的原右子节点成为原根的右子节点的左子节点，最终的根的原左子节点成为原根的右子节点。

删除:用与二叉查找树中相同的方法找到目标节点,然后如上述插入过程一样找到最小不平衡子树,在那之后,找到不平衡子树最高的子树和该高子树最高的子树（即高孙子）,从原最小不平衡子树的根到该高孙子树的根的相对方向决定了它属于哪一种情况(LL、RR、LR还是RL)，在插入时用同样的方法调整子树。
