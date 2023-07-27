class Base {
    private static String s = "The resuling matrix is";
    public static int matmul(int [ ][ ] a, int [ ][ ] b) {
        int r1 = a.length, c1 = a[0].length, r2 = b.length, c2 = b[0].length;
        int i = 0;
        int [ ][ ] result = new int[r1][c2];
        while(i < r1) {
            int j = 0;
            while(j < c2) {
                int k = 0, entry = 0;
                while(k < c1) {
                    entry = entry + a[i][k] * b[k][j];
                    k = k + 1;
                }
                result[i][j] = entry;
                j = j + 1;
            }
            i = i + 1;
        }
        System.out.println(s);
        i = 0;
        while(i < r1) {
            int j = 0;
            while(j < c2) {
                System.out.print(result[i][j]);
                System.out.print(" ");
                j = j + 1;
            }
            System.out.println("");
            i = i + 1;
        }
        return 1;
    }

    public static void main(String [ ] args) {
        System.out.println(args[0]);
        int m = 2, n = 3;
        int r1 = m, r2 = n, c1 = n, c2 = m;
        int [ ][ ] a = new int[r1][c1];
        a[0][0] = 1;
        a[0][1] = 1;
        a[0][2] = 2;
        a[1][0] = 4;
        a[1][1] = 3;
        a[1][2] = 0;
        int [ ][ ] b = new int[r2][c2];
        b[0][0] = 2;
        b[0][1] = 0;
        b[1][0] = 3;
        b[1][1] = 2;
        b[2][0] = 1;
        b[2][1] = 0;
        matmul(a, b);
    }
}