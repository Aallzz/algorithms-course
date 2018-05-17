import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;
 
public class _10_A {
 
    private static int n1;
    private static int n2;
    private static int m;
    private static List<Integer>[] g;
    private static int[] matching;
    private static boolean[] used;
 
//    private final static String file_input = "/home/alexander/study/main/programming/Java/labs/src/input.txt";
//    private final static String file_output = "/home/alexander/study/main/programming/Java/labs/src/output.txt";
 
    private final static String file_input = "matching.in";
    private final static String file_output = "matching.out";
 
    public static void main(String... args) throws Exception {
        Scanner sc = new Scanner(new File(file_input));
        BufferedWriter pr = new BufferedWriter(new FileWriter(file_output));
        n1 = sc.nextInt();
        n2 = sc.nextInt();
        m = sc.nextInt();
        g = new List[n1];
        for (int i = 0; i < n1; ++i) {
            g[i] = new ArrayList<>();
        }
        for (int i = 0; i < m; ++i) {
            int x = sc.nextInt();
            int y = sc.nextInt();
            x--; y--;
            g[x].add(y);
        }
        matching = new int[n2];
        used = new boolean[n1];
        Arrays.fill(matching, -1);
        int ans = 0;
        for (int i = 0; i < n1; ++i) {
            Arrays.fill(used, false);
            ans += dfs(i) ? 1 : 0;
        }
        pr.write(Integer.toString(ans));
        pr.close();
    }
 
    private static boolean dfs(int v) {
        if (used[v]) return false;
        used[v] = true;
        for (int to : g[v]) {
            if (matching[to] == -1 || dfs(matching[to])) {
                matching[to] = v;
                return true;
            }
        }
        return false;
    }
}
