sc = File.new("paths.in", "r");
 
$n, $m = sc.gets.chomp.split(' ').map {|i| i.to_i}
$g = Array.new($n) {Array.new}
$used = Array.new($n) {|x| x = false}
$matching = Array.new($n) {|x| x = -1}
 
def dfs(v) 
    return false if $used[v]
    $used[v] = true
    $g[v].each do |to| 
        if ($matching[to] == -1 || dfs($matching[to])) then
            $matching[to] = v
            return true;
        end
    end
    return false
end
 
$m.times do
    edge = sc.gets().chomp
    x, y = edge.split(' ').map {|i| i.to_i}
    x -= 1; y -= 1
    $g[y] << x
end
 
ans = 0
 
$n.times do |i|
    $used.map! {|x| x = false}
    ans += dfs(i) ? 1 : 0;
end
 
File.open("paths.out", 'w') { |file| file.write($n - ans)}
