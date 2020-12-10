{-
Harshal Dupare | 18MA20015
-}

-- sorts the list
qsort :: [Int] -> [Int]
qsort [] = []
qsort ( x : xs ) = qsort less_than_x ++ [x] ++ qsort greater_than_x -- take the less than and append before and grater than after the pivot
    where
        less_than_x = [ l | l <- xs, l <= x ]  -- compact notation using list comprehension for getting the less than or equal elements
        greater_than_x = [ r | r <- xs, x < r ] -- compact notation using list comprehension for getting the greater than elements

main = do
  let x = [9, 8, 7, 0, 1, 2, 3, 3, 7, -8, 9, 10, 5, 99]
  print $ qsort x
