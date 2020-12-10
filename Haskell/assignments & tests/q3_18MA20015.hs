{-
Harshal Dupare | 18MA20015
-}

-- returns the list which contains the elements less than or equal to x from the list (y:ys)
lower :: Int -> [Int] -> [Int]
lower _ [] = []
lower x (y : ys)
  | y <= x = y : lower x ys -- if less than or equal to then append
  | otherwise = lower x ys -- if not then dont append

-- returns the list which contains the elements greater than x from the list (y:ys)
greater :: Int -> [Int] -> [Int]
greater _ [] = []
greater x (y : ys)
  | y > x = y : greater x ys -- if greater than then append
  | otherwise = greater x ys -- if not then dont append

-- sorts the list
qsort :: [Int] -> [Int]
qsort [] = []
qsort (x : xs) = qsort (lower x xs) ++ [x] ++ qsort (greater x xs) -- take the less than and append before and grater than after the pivot

main = do
  let x = [9, 8, 7, 0, 1, 2, 3, 3, 7, -8, 9, 10, 5, 99]
  print $ qsort x
