{-
Harshal Dupare | 18MA20015
-}

-- takes lists of lists of ints and collapse it in a single list
collapse_list :: [[Int]] -> [Int]
collapse_list [] = []
collapse_list [x] = x
collapse_list (x:xs) = x ++ collapse_list xs

main = do
    print $ collapse_list [[1,2,3],[4,5,6]]

