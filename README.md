# VM - A simple Virtual-Machine 

## Pseudo-Code Input
```
var a = 42
print a

var b = 23
print b

var c = a + b
print c

print 'Hallo Welt'
print 42
print 3.14

if a > b {
    print 'b is lower than a'
} else {
    print 'a is lower than b'
}

var i = 0
while i < 5 {
    print i
}
```

## OpCode Output:
```
assign &0, 42
print &0
assign &1, 23
print &1
add &0, &1
assign &2, ~0
print &2
print 'Hallo Welt'
print 42
print 3.14
is_lower &0, &1
skip_if_not #2
print 'a is lower than b'
skip #1
print 'b is lower than a'
assign &3, 0
is_lower_or_equal 5, &3
skip_if #4
print &3
add &3, 1
assign &3, ~0
skip #-5
```

## Console Output / Interpreation:
```
42
23
65
Hallo Welt
42
3.14
b is lower than a
0
1
2
3
4
```
