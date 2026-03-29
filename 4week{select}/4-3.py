import sys

class Node:
  def __init__(self, item):
    self.item = item
    self.left = None
    self.right = None

class BST:
  def __init__(self):
    self.root = None
    
  def insert(self, item):
    new_node = Node(item) #객체 생성
    
    if self.root is None:
      self.root = new_node
      return
    
    current = self.root
    while True:
      if item < current.item:
        if current.left is None:
          current.left = new_node
          break
        current = current.left
      else:
        if current.right is None:
          current.right = new_node
          break
        current = current.right

  def find_node(self, item):
    current = self.root
    while current is not None:
      if item == current.item:
        return True
      elif item < current.item:
        current = current.left
      else:
        current = current.right
    return False

  def delete_node(self, item):
    if not self.find_node(item):
      return False
    self.root = self._delete_node(self.root, item)
    return True

  def _delete_node(self, node, target):
    if node is None:
      return node
    if target < node.item:
      node.left = self._delete_node(node.left, target)
    elif target > node.item:
      node.right = self._delete_node(node.right, target)
    else: #삭제할 노드 찾았을 때
      if node.left is None and node.right is None: #자식 노드가 없는 경우
        return None
      elif node.left is None: #자식 노드가 오른쪽에만 있는 경우
        return node.right
      elif node.right is None: #자식 노드가 왼쪽에만 있는 경우
        return node.left
      #자식 노드가 둘 다 있는 경우
      else:
        successor = self._find_min(node.right)
        node.item = successor.item #오른쪽 노드 중에 가장 작은 노드를 현재 노드에 복사
        node.right = self._delete_node(node.right, successor.item) #복사한 노드 삭제
    return node
        
  
  def _find_min(self, node):
    current = node
    while current.left is not None:
      current = current.left
    return current
    
  def preorder(self, node):
    if node:
      print(node.item, end=' ')
      self.preorder(node.left)
      self.preorder(node.right)

  def inorder(self, node):
    if node:
      self.inorder(node.left)
      print(node.item, end=' ')
      self.inorder(node.right)
  def postorder(self, node):
    if node:
      self.postorder(node.left)
      self.postorder(node.right)
      print(node.item, end=' ')
      
  
  
if __name__ == "__main__":

  input_nodes = sys.stdin.readline().strip()

  nodes = list(map(int, input_nodes.strip('[]').split(',')))

  N = int(input()) #find node
  M = int(input()) #insert node
  L = int(input()) #delete node
  
  bst = BST()
  for node in nodes:
    bst.insert(node)
  
  print(bst.find_node(N))
  bst.preorder(bst.root)
  print()
  bst.insert(M)
  bst.inorder(bst.root)
  print()
  print(bst.delete_node(L))
  bst.postorder(bst.root)
  print()
  
  
  #print(f"{bst.root.item} {bst.root.left.item} {bst.root.right.item}")
