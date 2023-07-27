class Base {
    public static void main(String [ ] args) {
        System.out.println(args[0]);
        int i = 0;
        while(i < 5) {
            int j = 0;
            while(j < i) {
                System.out.println(j);
                j = j + 1;
            }
            i = i + 1;
        }
    }
}