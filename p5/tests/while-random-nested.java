class Random {
    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        int m = Integer.parseInt(args[1]);
        int a = Integer.parseInt(args[2]);
        int b = Integer.parseInt(args[3]);
        int i = 0;
        int j = 0;
        int sum = 0;

        while (i < n) {
            while (j < m) {
                sum = sum + b;
                j = j + 1;
            }
            j = 0;
            sum = sum + a;
            i = i + 1;
        }

        System.out.println(sum);
    }
}