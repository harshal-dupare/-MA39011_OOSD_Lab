-- stack

data Stack a = Empty | Value a (Stack a)
  deriving (Eq, Show)

push :: a -> Stack a -> Stack a
push x Empty = Value x (Empty)
push x s = Value x (s)

pop :: Stack a -> Stack a
pop (Value _ (q)) = q

top :: (Show a) => Stack a -> a
top (Value x (_)) = x

-- stack ends

-- queue

data Queue a = Empt | Node (Queue a) a
  deriving (Show)

enque :: a -> Queue a -> Queue a
enque x Empt = Node (Empt) x
enque y (Node q x) = Node (enque y q) x

deque :: Queue a -> Queue a
deque Empt = Empt
deque (Node q _) = q

front :: Queue a -> a
front (Node _ x) = x

-- queue ends

-- queue 2

data Que a = Que [a] [a]
  deriving (Show)

enq :: a -> Que a -> Que a
enq x (Que psl pol) = (Que (x : psl) pol)

deq :: Que a -> (a, Que a)
deq (Que psl []) = deq (Que [] (reverse psl))
deq (Que psl (x : polx)) = (x, (Que psl polx))

isempty :: Que a -> Bool
isempty (Que [] []) = True
isempty (Que _ _) = False

-- queue 2 ends


-- PNEx

-- need a mixed type

data Token = Val Int | Operator Char

type Expression = [Token]

eval :: Stack Int -> Token -> Stack Int
eval s (Val i) = push i s
eval s (Operator o)
  | o == '+' = push (v2 + v1) s'
  | o == '*' = push (v2 * v1) s'
  | o == '-' = push (v2 - v1) s'
  | o == '/' = push (div v2 v1) s'
  where
    v1 = top s
    v2 = top $ pop $ s
    s' = pop $ pop $ s

evalexp :: Stack Int -> Expression -> Stack Int
evalexp s [] = s
evalexp s (t : exp) = evalexp (eval s t) exp

char2int :: String -> Int
char2int s = read s :: Int

makeexp :: [String] -> Expression
makeexp [] = []
makeexp (x : xs)
  | x == "+" = (Operator '+') : (makeexp xs)
  | x == "*" = (Operator '*') : (makeexp xs)
  | x == "-" = (Operator '-') : (makeexp xs)
  | x == "/" = (Operator '/') : (makeexp xs)
  | otherwise = (Val (char2int x)) : (makeexp xs)


-- PNEx ends

main = do
  let q = Empt
  let q1 = enque 1 q
  let qq = enque 3 q1
  let qQq = enque (-1) qq
  let x = front q1
  print $ q1
  print $ x
  print $ qq
  print $ qQq
  let q2 = deque qQq
  print $ q2
  let dq = Que [] []
  let dqq = enq 5 $ enq 3 dq
  print $ dqq
  let d = deq dqq
  print $ d
  let e = makeexp $ words "10 2 + 3 - 5 * 2 /"
  let v = evalexp Empty e
  print $ v