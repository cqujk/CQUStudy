## 不是所有规则都必须要有动作
如果某个规则没有动作，那么默认动作为
```
$$=$1;
```
```
exp: NUM /*{ $$=$1;}*/
```

    