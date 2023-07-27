class Base {
    public static int method(int a) {
        System.out.println(a);
        return 3;
    }
    
	public static void main(String[] args){
        System.out.println(args[0]);
        int b = 352;
        int a = method(b);
        System.out.println(a);
	}
}
