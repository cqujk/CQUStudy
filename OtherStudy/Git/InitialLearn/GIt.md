GIt 有三东西，一个是版本库，一个是工作区，还有一个是暂存区
Git 提交分为两步，第一个先是添加 add, 然后再是 commit 提交
![[Pasted image 20240927115647.png]]
第一步是用 `git add` 把文件添加进去，实际上就是把文件修改*添加到暂存区*
第二步是用 `git commit` 提交更改，实际上就是把*暂存区的所有内容提交到当前分支。*
需要提交的文件*修改通通放到暂存区*，然后，一次性*提交暂存区的所有修改*

`git checkout` 其实是用*版本库里的版本*替换*工作区的版本*，无论工作区是修改还是删除，都可以“一键还原”
	从来没有被添加到版本库就被删除的文件，是无法恢复的
		就是说只 add 了，但是没有 commit、放在暂存区的东西，是不行的




**This key is not known by any other names**

- 这意味着你的SSH客户端的 `known_hosts` 文件中没有这个密钥的记录

- 输入了 `yes` 来确认你想要继续连接到这个服务器。
    
- SSH客户端将这个密钥添加到了 `~/.ssh/known_hosts` 文件中，这样在未来的连接中就不会再提示你确认

这个就是先
```plain
git remote add origin git@github.com:michaelliao/learngit.git
```
把本地仓库的和远程仓库关联起来，在关联之前，应当*先在远程仓库上输入在本地仓库上创建的公钥*，即 rsa
	把上面的 `michaelliao` 替换成你自己的 GitHub 账户名，否则，你在本地关联的就是我的远程库，关联没有问题，但是你以后推送是推不上去的，*因为你的 SSH Key 公钥不在我的账户列表中*
		*只有公钥已经存在于远程仓库的账户列表当中，才可以正式建立关联*
然后进行 commit 提交
	如果是第一次提交，那么 ssh 客户端上是不存在相对应的私钥的，所以需要进一步 yes提交，这个时候本地仓库上生成的私钥就会记录在远程仓库上
		之后再提交，用的就是这个私钥了

有 Git 就已经有仓库了，本地仓库；
github只是把本地仓库变成远程仓库了而已


 Git push -u origin master
	 是把当前分支`master`推送到远程仓库`origin`上
	 加上了`-u`参数，Git不但会把本地的`master`分支内容推送的远程新的`master`分支，还会把本地的`master`分支和远程的`master`分支关联起来
		 从现在起，只要本地作了提交，就可以通过命令： 
```plain
$ git push origin master
```
把本地 `master` 分支的最新修改推送至GitHub
	前一个是远程仓库的对象，后一个是本地仓库的分支

“删除”其实是解除了本地和远程的绑定关系
要关联一个远程库，使用命令
`git remote add origin git@server-name:path/repo-name.git`；
	关联一个远程库时必须给远程库指定一个名字，`origin`是默认习惯命名；
关联后，使用命令 `git push -u origin master` 第一次推送 `master` 分支的所有内容；
	这个 origin 就是上一步关联远程库的名字


# 从远程仓库 Clone
要克隆一个仓库，首先必须知道仓库的地址，然后使用`git clone`命令克隆。
Git支持多种协议，包括 `https`，但 `ssh` 协议速度最快

**两种方式，**
*第一种是用 SSH 的方式*
![[Pasted image 20240927164213.png]]
*第二种是用 https的*
用`https://github.com/michaelliao/gitskills.git`这样的地址
![[Pasted image 20240927164231.png]]

使用 `https` 除了速度慢以外，还有个最大的麻烦是每次推送都必须输入口令，但是在某些只开放 `http` 端口的公司内部就无法使用 `ssh` 协议而只能用 `https`

# 分支

`HEAD` 严格来说不是指向提交，而是指向 `master`，`master` 才是指向提交的，所以，`HEAD` 指向的就是当前分支
一开始的时候，`master`分支是一条线，Git用`master`指向最新的提交，再用`HEAD`指向`master`，就能确定当前分支，以及当前分支的提交点