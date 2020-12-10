-- do heap for test
-- this defines in order defination
-- the data is a hence it holds the data a ( a == abstract data type )

data Btree a = Empty | Node (Btree a) a (Btree a) -- this defines how tree looks like the tree and this is inorder defination

lefttree :: Btree a -> Btree a
lefttree Empty = Empty
lefttree (Node lt _ _) = lt

righttree :: Btree a -> Btree a
righttree Empty = Empty
righttree (Node _ _ rt) = rt

inorderwalk :: Btree a -> [a]
inorderwalk Empty = []
inorderwalk (Node lt x rt) = (inorderwalk lt) ++ [x] ++ (inorderwalk rt)

preorderwalk :: Btree a -> [a]
preorderwalk Empty = []
preorderwalk (Node lt x rt) = [x] ++ (preorderwalk lt) ++ (preorderwalk rt)

postorderwalk :: Btree a -> [a]
postorderwalk Empty = []
postorderwalk (Node lt x rt) = (postorderwalk lt) ++ (postorderwalk rt) ++ [x]

insert :: (Ord a) => a -> Btree a -> Btree a
insert y Empty = Node Empty y Empty
insert y (Node lt x rt) -- need to check equality case and returun the original tree again as no repeated value
  | y < x = Node (insert y lt) x rt
  | otherwise = Node lt x (insert y rt)

maketree :: (Ord a) => [a] -> Btree a
maketree [] = Empty
maketree [x] = Node Empty x Empty
maketree (x : xs) = insert x (maketree xs)

treesize :: Btree a -> Int
treesize Empty = 0
treesize (Node lt _ rt) = 1 + (treesize lt) + (treesize rt)

treeheight :: Btree a -> Int
treeheight Empty = 0
treeheight (Node lt _ rt) = 1 + max (treeheight lt) (treeheight rt)

maxelement :: Btree a -> a
maxelement (Node _ x Empty) = x
maxelement (Node _ _ rt) = maxelement rt

minelement :: Btree a -> a
minelement (Node Empty x _) = x
minelement (Node lt _ _) = minelement lt

delminelement :: Btree a -> Btree a
delminelement (Node Empty _ rt) = rt
delminelement (Node lt x rt) = (Node (delminelement lt) x rt)

delelement :: (Ord a) => a -> Btree a -> Btree a
delelement _ Empty = Empty
delelement c (Node lt x Empty)
  | c < x = (Node (delelement c lt) x Empty)
  | c > x = (Node lt x Empty)
  | otherwise = lt
delelement c (Node lt x rt)
  | c < x = (Node (delelement c lt) x rt)
  | c > x = (Node lt x (delelement c rt))
  | otherwise = (Node lt (minelement rt) (delminelement rt))

isincreasing :: (Ord a) => [a] -> Bool
isincreasing [] = True
isincreasing [_] = True
isincreasing (x : y : xs) = (x <= y) && (isincreasing (y : xs))

isbst :: (Ord a) => Btree a -> Bool
isbst Empty = True
isbst t = isincreasing (inorderwalk t)

find :: (Ord a) => a -> Btree a -> Bool
find _ Empty = False
find y (Node lt x rt)
  | y == x = True
  | y < x = find y lt
  | otherwise = find y rt


{-
stringtol :: String -> [String]
stringtol s = words s

toint :: String -> Int
toint x = read x :: Int

append :: a -> [a] -> [a]
append x []= [x]
append x (y:ys) = y:(append x ys)

rPN :: [String] -> Int
rPN [x] = toint x
rPN (x:xs)
    | last xs == "+" = toint x + rPN (init xs)
    | last xs == "*" = toint x * rPN (init xs)
    | last xs == "-" = toint x - rPN (init xs)
    | otherwise = toint x
-}

-- bfs dfs
-- bfs dfs

-- Balanced Binary search tree




-- Balanced Binary search tree


main = do
  let x = Node Empty 5 Empty
  let l = [-7, 7, 8, -8, 9, -9, 10, -10, 0]
  print $ l
  print $ inorderwalk x
  let y = insert 3 x
  print $ inorderwalk y
  print $ preorderwalk y
  print $ postorderwalk y
  print $ treesize y

  let t = maketree l
  print $ inorderwalk t
  print $ treesize t

  print $ treeheight t
  print $ minelement $ t
  print $ maxelement $ t
  print $ preorderwalk $ delminelement $ (Node Empty 8 Empty)
  print $ preorderwalk $ delelement 7 (Node (Node Empty 6 Empty) 7 Empty)

  print $ isbst t
  print $ isbst (Node (Node Empty 7 Empty) 6 Empty)
  print $ preorderwalk t
  print $ find 7 t
  print $ find 79 t