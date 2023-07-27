class Random {
    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        int a = Integer.parseInt(args[1]);
        int b = Integer.parseInt(args[2]);
        int c = Integer.parseInt(args[3]);
        int count = 0;
        int sum = 0;

        while (count < n) {
            sum = sum + a + b + c;
            count = count + 1;
        }

        System.out.println(sum);
    }
}

