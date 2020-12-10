{-
Harshal Dupare | 18MA20015
-}

-- tree
data Btree a = Empty | Node (Btree a) a (Btree a)

-- function to get the height
height :: Btree Int -> Int
height Empty = 0
height (Node lt _ rt) = max ((height lt) + 1) ((height rt) + 1)

-- function to get the list list
getlist :: Btree Int -> Int -> [Int]
getlist Empty _ = []
getlist (Node _ x _) 1 = [x]
getlist (Node Empty _ rt) i = getlist rt (i -1)
getlist (Node lt _ Empty) i = getlist lt (i -1)
getlist (Node lt _ rt) i = getlist lt (i -1) ++ getlist rt (i -1)

-- function to show the bst
showbst :: Btree Int -> Int -> Int -> [Int]
showbst t i h =
  if (i <= h)
    then getlist t i ++ showbst t (i + 1) h
    else []

main = do
  let tree = (Node Empty 1 (Node (Node (Node Empty 2 Empty) 4 Empty) 7 Empty))
  let hig = height tree
  print $ hig
  print $ showbst tree 1 hig