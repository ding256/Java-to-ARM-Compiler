class Base {
	public static void main(String[] args) {
        System.out.println(args[0]);
		if(false) {
            System.out.println("not printed");
        } else {
            int a = 6;
            while(a > 0) {
                System.out.println(a + 9);
                a = a - 1;
            }
        }
	}
}
