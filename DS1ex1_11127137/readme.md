


```
maze[x][y] := the cell at (x,y) of the maze.
cur_x, cur_y := current position.
cur_dir := current direction.
G := the number of remaining goals.
tmpP := an empty stack to store temporary path.
P := an array of empty stacks to store the paths to the goals.

func DFS(cur_x, cur_y): f, f is whether G is 0 or not.

	if G is 0:
		return SUCCESS
	end if
	if cur_x or cur_y exceeds the boundary:
		return FAIL
	end if
	if maze[cur_x][cur_y] has been visited:
		return FAIL
	end if
	
	Mark maze[cur_x][cur_y] as visited.
	
	tmpP.push(maze[cur_x][cur_y])
	
	if maze[cur_x][cur_y] is a goal:
		P.push(tmpP)
		G := G - 1
	end if
	
	for k in [0, 3]:
		switch ( cur_dir ):
			case right:
				nxt_x := cur_x + 1
			case down:
				nxt_y := cur_y + 1
			case left:
				nxt_x := cur_x - 1
			case up:
				nxt_y := cur_y - 1
		end switch
		
		DFS( nxt_x, nxt_y )
		
		cur_dir := next direction
		
	end for
	
	tmpP.pop()
	
	return G is 0
end func
```