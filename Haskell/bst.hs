-- balanced BST

-- tree is either empty or has a node structure of (Node left_tree value height right_tree)
data Avl a = Empty | Node (Avl a) a Int (Avl a)
  deriving (Show, Eq)


-- function to get the height of the tree
height :: Avl a -> Int
height Empty = 0
height (Node _ _ h _) = h


-- function to get the balance of the node
balance :: Avl a -> Int
balance Empty = 0 -- if empty then return 0
balance (Node lt _ _ rt) = height lt - height rt -- if left and right tree there just return the difference in height


-- function to rotate the tree right
rightrotate :: Avl a -> Avl a
rightrotate Empty = Empty -- if empty just return it back
rightrotate (Node Empty x h rt) = (Node Empty x h rt) -- if theres no left tree then return the tree back
rightrotate (Node (Node llt lx lh lrt) x h rt) = Node llt lx newh (Node lrt x newrh rt) -- if left tree is there then just change the structrue and return
  where
    newrh = 1 + max (height lrt) (height rt) -- just take the 1 + max height of the left and right tree in new structure
    newh = 1 + max newrh lh -- just take the 1 + max height of the left and right tree in new structure


-- function to rotate the tree left
leftrotate :: Avl a -> Avl a
leftrotate Empty = Empty -- if empty just return it back
leftrotate (Node lt x h Empty) = (Node lt x h Empty) -- if theres no right tree then return the tree back
leftrotate (Node lt x h (Node rlt rx rh rrt)) = Node (Node lt x newlh rlt) rx newh rrt -- if right tree is there then just change the structrue and return
  where
    newlh = 1 + max (height lt) (height rlt) -- just take the 1 + max height of the left and right tree in new structure
    newh = 1 + max newlh rh -- just take the 1 + max height of the left and right tree in new structure
    -- function to return height of the tree by just looking it up


-- by left heavy we will mean that height of left tree is more than right tree and similary for right heavy


-- rebalance the tree
rebalance :: Avl a -> Avl a
rebalance (Node lt x h rt)
  | abs (bal) < 2 = Node lt x h rt -- if balanced then return as it is
  | (bal == 2) && (lbal /= -1) = rightrotate (Node lt x h rt) -- if left heavy tree and left tree is not right heavy then rotate right
  | (bal == 2) && (lbal == -1) = rightrotate (Node (leftrotate lt) x h rt) -- if left heavy tree and left tree is right heavy then first left rotate left tree then right rotate the main tree
  | (bal == -2) && (rbal /= 1) = leftrotate (Node lt x h rt) -- if right heavy tree and right tree is not left heavy then rotate left
  | (bal == -2) && (rbal == 1) = leftrotate (Node lt x h (rightrotate lt)) -- if right heavy tree and right tree is left heavy then first right rotate right tree then left rotate the main tree
  where
    bal = balance (Node lt x h rt) -- balance factor of main tree
    lbal = balance lt -- balance factor of left tree
    rbal = balance rt -- balance factor of right tree


-- find function returns true if there in the tree
find :: (Ord a) => a -> Avl a -> Bool
find _ Empty = False -- if empty then return true
find c (Node lt x _ rt)
  | c == x = True -- if same as the node value return True
  | c < x = find c lt -- if less than node value find in left tree
  | otherwise = find c rt -- if more than node value find in right tree


-- insert the value into tree
insert :: (Ord a) => a -> Avl a -> Avl a
insert c Empty = Node Empty c 1 Empty -- if inserting in empty tree just insert and make height 1
insert c (Node lt x h rt)
  | x == c = (Node lt x h rt) -- if equal to the node just return the tree as it is as not duplicates allowed
  | c < x = rebalance (Node lt' x lh' rt) -- if less than the value in node just insert in left tree and reblance the tree
  | otherwise = rebalance (Node lt x rh' rt') -- if more than the value in node just insert in right tree and reblance the tree
  where
    lt' = insert c lt -- insert in left tree
    lh' = 1 + max (height rt) (height lt') -- get the new height of the left tree
    rt' = insert c rt -- insert in right tree
    rh' = 1 + max (height lt) (height rt') -- get the new height of the right tree


-- function to delete the max node from the tree and return the max value and the resulting tree
delmaxnode :: Avl a -> (a, Avl a)
delmaxnode (Node lt x _ Empty) = (x, lt) -- if right tree is empty just remove this value and return the value and left tree
delmaxnode (Node lt x _ rt) = (y, nt) -- delete from right tree and rebalance
  where
    (y, t) = delmaxnode rt -- delete from right tree
    h' = 1 + max (height lt) (height t) -- get new height of tree
    nt = rebalance (Node lt x h' t) -- rebalance the tree and get new tree

-- function to delete the node
delete :: (Ord a) => a -> Avl a -> Avl a
delete _ Empty = Empty -- if deleting from empty tree just return the empty tree as nothing to delete
delete c (Node lt x h rt)
  | c < x = rebalance (Node lt' x lh' rt) -- if less than the value in node just delete the value from left tree and reblance the tree
  | c > x = rebalance (Node lt x rh' rt') -- if more than the value in node just delete the value from right tree and reblance the tree
  | otherwise = if (lt == Empty) then rt else rebalance (Node nt nx nxh' rt) -- if value is in this node to delete if left tree is empty then just delete it and return right tree
  -- if its not empty then we replace it the max value node from the left tree and remove that max value node formm the left tree and rebalance it
  where
    lt' = delete c lt -- if in left tree we need to delete from left tree
    lh' = 1 + max (height lt') (height rt) -- get the new left height
    rt' = delete c rt -- if in right tree we need to delete from right tree
    rh' = 1 + max (height rt') (height lt) -- get the new right height
    (nx, nt) = delmaxnode lt -- if in the value is in this level
    nxh' = 1 + max (height nt) (height rt) -- new height of the tree after deleting

-- makes avl tree from the list
makeavltree :: (Ord a) => [a] -> Avl a
makeavltree [] = Empty -- if empty list just return empty tree
makeavltree [x] = (Node Empty x 1 Empty) -- if only element then return the node
makeavltree (x : xs) = insert x (makeavltree xs) -- insert 1st element of list in the tree formed by all the other elements

-- function to get the list from the Avl tree
inorderwalk :: Avl a -> [(a, Int)]
inorderwalk Empty = []
inorderwalk (Node lt x h rt) = (inorderwalk lt) ++ [(x, h)] ++ (inorderwalk rt)

main = do
  let l = [1 .. 20]
  print $ l
  let t = makeavltree l
  print $ "height is :\n"
  print $ height t
  print $ "\n"
  print $ inorderwalk t
  let t1 = delete 1 t
  print $ inorderwalk t1
  let t11 = delete 11 t1
  print $ inorderwalk t11