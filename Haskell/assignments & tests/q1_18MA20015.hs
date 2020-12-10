{-
Harshal Dupare | 18MA20015
-}

-- returns the i whose cube is greater than n ,i.e. i^3 > n 
greater_cube :: Int -> Int -> Int
greater_cube _ 0 = 1
greater_cube _ 1 = 2
greater_cube i n
    | i^3 > n = i
    | otherwise = greater_cube (i+1) n

-- returns the list of Tuples which satisfy the constrains n
two_ways_cube :: Int -> [(Int, Int)]
two_ways_cube n = [(x, y) | x <- [1 .. greater_cube 0 n], y <- [1 .. greater_cube 0 n], n == x * x * x + y * y * y, y > x]

-- prints the list of tuples
issumcube :: [(Int, Int)] -> IO ()
issumcube x
  | (length x) > 1 = print $ x
  | (length x) <= 1 = print $ "Not possible to write as sum of 2 different pairs of cubes" -- if not possible then inform so

main = do
  let x = two_ways_cube (69634)
  issumcube x

