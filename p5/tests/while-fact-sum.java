class FactorialSum {
    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        int sum = 0;
        int i = 1;

        while (i <= n) {
            int factorial = 1;
            int j = 1;
            while (j <= i) {
                factorial = factorial * j;
                j = j + 1;
            }
            sum = sum + factorial;
            i = i + 1;
        }

        System.out.println(sum);
    }
}
