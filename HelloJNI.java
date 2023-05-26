import java.util.Scanner;

public class HelloJNI { 

   static {
      System.loadLibrary("JNI");
   }

   private native void sayHello();
   private native void update(int bid,int q);
   private native void add(int bid,String name,String author, String edd, String pub,int q);
   private native void delete(int bid);
   private native void user_list();
   private native void borrow(int bid,String username);
   private native void Return(int bid,String username);
   private native void myBooks(String username);
   private native boolean checkuser(String username, String password);
   private native boolean checkadmin(String username, String password);

   public static void main(String[] args) {
      System.out.print("Welcome\n");
      Scanner sc = new Scanner(System.in);
      while (true)
      {
         System.out.print("Enter 1 for login and 2 for logout:");
         int log = sc.nextInt();

         if(log == 1)
         {
            System.out.print("Enter username:");
            String username = sc.next();
            System.out.print("Enter Password:");
            String password = sc.next();
            if(new HelloJNI().checkadmin(username,password))
            {
               System.out.println("Logged in as Admin");
               while (true)
               {
                  System.out.println("\nEnter the choice \n1. View 2. Update 3. Add 4. Delete 5.User list 0.Logout::\n");
                  int ch = sc.nextInt();

                  if(ch==1) //VIEWALL
                  {
                     System.out.println("ViewAll");
                     new HelloJNI().sayHello();
                  }
                  else if (ch == 2) //UPDATE
                  {
                     System.out.print("Enter the Book Id:");
                     int bid = sc.nextInt();
                     System.out.print("Enter the Quantity:");
                     int q = sc.nextInt();
                     
                     new HelloJNI().update(bid,q);
                     
                  } 
                  else if (ch ==3) //ADD
                  {
                     System.out.print("Enter the book id:");
                     int bid = sc.nextInt();
                     System.out.print("Enter the Book name:");
                     sc.nextLine();
                     String name = sc.nextLine();
                     System.out.print("Enter the Author Name:");
                     String author = sc.nextLine();
                     
                     System.out.print("Enter the Edition:");
                     String edd = sc.next();
                     System.out.print("Enter the Publisher Name:");
                     String pub = sc.nextLine();
                     sc.nextLine();
                     System.out.print("Enter Quantity:");
                     int q = sc.nextInt();

                     new HelloJNI().add(bid,name,author,pub,edd,q);
                  }
                  else if (ch == 4 ) //DELETE
                  {
                     System.out.print("Enter the Book id to delete:");               
                     int bid = sc.nextInt();

                     new HelloJNI().delete(bid);
                  }

                  else if (ch == 5) //USERLIST
                  {
                     new HelloJNI().user_list();              
                  }

                  else if (ch == 0) 
                  {
                     System.out.println("logout");
                     break;               
                  }
                  else{
                     System.out.println("Enter the correct number");
                  }
               }
            }

            if(new HelloJNI().checkuser(username,password))
            {
               System.out.println("Logged in as user");
               while (true)
               {
                  System.out.println("\nEnter the choice \n1. View 2. Borrow 3. Return 4. My Books 0. Logout::\n");
                  int ch = sc.nextInt();

                  if(ch==1) //VIEWALL
                  {
                     new HelloJNI().sayHello();
                  }
                  else if (ch == 2) //BORROW
                  {
                     System.out.print("Enter the Book Id:");
                     int bid = sc.nextInt();
                     
                     new HelloJNI().borrow(bid,username);                  
                  } 
                  else if (ch ==3) //RETURN
                  {
                     System.out.println("Enter the book id:");
                     int bid = sc.nextInt();

                     new HelloJNI().Return(bid,username);
                  }
                  else if (ch == 4 ) //MYBOOKS
                  {
                     System.out.println("mYBOOKS");             

                     new HelloJNI().myBooks(username);
                  }
                  else if (ch == 0) {
                     System.out.println("logout");
                     break;               
                  }
                  else{
                     System.out.println("Enter the correct number");

                  }      
               }
            }
         }
         else{
            System.out.println("Logging out...");
            System.exit(10);
         }
      }
      //new HelloJNI().sayHello();  // Create an instance and invoke the native method
   }
}