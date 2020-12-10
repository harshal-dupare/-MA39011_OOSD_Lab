{-
Harshal Dupare | 18MA20015
-}

findpairs :: Int -> [Int]
findpairs n = head [[x, y, z, w] | x <- [0 .. n], y <- [0 .. n], z <- [0 .. n], w <- [0 .. n], x * x + y * y + z * z + w * w == n]

main = do
  let n = 230
  print $ findpairs n