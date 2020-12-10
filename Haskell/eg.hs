data Btree a = Empty | Node (Btree a) a (Btree a)

insert :: (Ord a) => a -> Btree a -> Btree a
insert y Empty = Node Empty y Empty
insert y (Node lt x rt)
  | y < x = Node (insert y lt) x rt
  | otherwise = Node lt x (insert y rt)

inorderwalk :: Btree a -> [a]
inorderwalk Empty = []
inorderwalk (Node lt x rt) = (inorderwalk lt) ++ [x] ++ (inorderwalk rt)

isincreasing :: (Ord a) => [a] -> Bool
isincreasing [] = True
isincreasing [_] = True
isincreasing (x : y : xs) = (x <= y) && (isincreasing (y : xs))

isbst :: (Ord a) => Btree a -> Bool
isbst Empty = True
isbst t = isincreasing (inorderwalk t)

main = do
  let x = Node Empty 5 (Node Empty 7 (Node Empty 1 Empty))
  print $ inorderwalk x
  let y = insert 3 x
  print $ inorderwalk y