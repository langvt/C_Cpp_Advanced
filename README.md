# C_Cpp_Advanced

<details>
  <summary><h1>C</h1></summary>

<details>
  <summary><h2>Quá trình biên dịch</h2></summary>

Quy trình biên dịch là quá trình chuyển đổi từ ngôn ngữ bậc cao (NNBC) (C/C++, Pascal, Java, C#…) sang  ngôn ngữ máy , để máy tính có thể hiểu và thực thi.
### Quá trình biên dịch bao gồm 4 giai đoạn:
- Giai đoàn tiền xử lý (Pre-processor)
- Giai đoạn dịch NNBC sang Asembly (Compiler)
- Giai đoạn dịch asembly sang ngôn ngữ máy (Asember)
- Giai đoạn liên kết (Linker)

    ![compiler](https://github.com/langvt/C_Cpp_Advanced/blob/main/images/process_compiler.png)


- Cấu trúc của một chương trình:

	```C

    #include<stdio.h> (thư viện, có thể là một file khác với include"file1")

    #define Max 10 (macro)

    //this is function
        void test(){
            prinf("this is function");
        }
    int main(){
        {
            test();
            return 0;
        }
    }





**_Pre-processor (Giai đoạn tiền xử lý):_**
- 1 Project có nhiều file:`a.h, b.h, a.c, b.c `và file `main.c` sau quá trình tiền xử lý thành 1 file duy nhất là file `main.i`.
- Lệnh trong CMD là: `gcc -E main.c -o main.i`

**Việc xảy ra trong quá trình tiền xử lý:**
- Nhận mã nguồn
- Xóa bỏ cmt,ghi chú.
- Chỉ thị tiền xử lý (bắt đầu bằng #) được xử lý.
	- Chỉ thị tiền xử lý dùng để chỉ những thông tin được xử lý ở quá trình tiền xử lý ( Preprocessor). Chia làm 3 nhóm chính:
	- `#include`:Chỉ thị `#include` dùng để chèn nội dung của một file vào mã nguồn chương trình
	- `#define, #undef`:Macro được định nghĩa bằng cách dùng `#define` .Macro là từ dùng để chỉ những thông tin được xử lý ở tiền xử lý
	
		- ví dụ:
		```C
		#define display_sum(a,b) \ // xuống dòng
			printf("this is macro to sum 2 number \n");\
			printf("result is:%d \n",a+b);// dòng cuối cùn không cần\

		int main(){
			display_sum(5,6);
			return 0;
		}
		```
	
	- `#undef`:
		- Dùng để hủy định nghĩa 1 macro đã dc định nghĩa trước đó bằng `#define`.
		- Nếu hai hoặc nhiều tệp tiêu đề có cùng tên macro, chúng có thể xung đột với nhau. Việc sử dụng các chỉ thị này giúp ngăn chặn các xung đột này.

		- ví dụ:
		```C
		#include <stdio.h>
		#include "nhietdo.c"
		#include "doam.c"
		// trong 2 file đều có macro lần lượt là:
		//#define cam_bien 10(nhietdo.c)
		//#define cam_bien 20(doam.c)

		int main(){
			#undef cam_bien
			#define cam_bien 40
			return 0;
		}
		```
	- `#if, #elif, #else, #ifdef, #ifndef`
	- `#if`: Sử dụng để bắt đầu 1 điều kiện tiền xử lý.Nếu đúng thì các dòng lệnh sau `#if` sẽ được biên dịch , sai sẽ bỏ qua đến khi gặp`#endif`.
	- `#elif`: Để thêm 1 ĐK mới khi `#if` hoặc `#elif` sai.
	- `#else`: Dùng khi không có ĐK nào đúng
	- `#ifdef` : Dùng để kiểm tra 1 macro định nghĩa hay chưa.Nếu định nghĩa rồi thì mã sau ifdef sẽ được biên dịch.
	- `#ifndef`: Dùng để kiểm tra 1 macro định nghĩa hay chưa.Nếu chưa định nghĩa thì mã sau ifndef sẽ được biên dịch.Thường dùng để kiểm tra macro đó đã dc định nghĩa trong file nào chưa, kết thúc thì `#endif`
	- ví dụ:
		```C

		#define max 6
		#if max ==20
		int a =10;
		#elif max <20
		int a =6;
		#endif
		#include <stdio.h>
		int main()
		{
			printf("a bang %d",a);// a bằng 10
			return 0;
		}

		```

	**Mục đích để tránh Định Nghĩa Nhiều Lần và Xung Đột**
	- Ví dụm trong 1 file `main.h`
	```C
	#ifndef __MAIN_H__
	#define __MAIN_H__
	#include<stdio.h>
	#endif 
	```
	- 1 số toán tử trong Macro: 
		- #define STRINGSIZE(x) #x
		- Ví dụ:
			```C
			#define STRINGSIZE(x) #x
			#define DATA 40

			int main(){
				prinf("the value: %s\n",STRINGSIZE(DATA));
				return 0;
			// sẽ in ra the value: DATA
			}
			```
		- Variadic Macro: Là 1 macro cho phép nhận 1 số lượng biến tham số có thể thay đổi
		<details>
		<summary>Ví dụ:</summary>
		
		```C

			#include <stdio.h>

			#define print_menu_item(...) \
				do { \
					const char *items[] = {__VA_ARGS__}; \
					int n = sizeof(items) / sizeof(items[0]); \
					for (int i = 0; i < n; i++) { \
						print_menu_item(i + 1, items[i]); \
					} \
				} while (0)

			#define case_option(number, function) \
				case number: \
					function(); \
					break;

			#define handle_option(option, ...) \
				switch (option) { \
					__VA_ARGS__ \
					default: \
						printf("Invalid option!\n"); \
				}

			void print_menu_item(int number, const char *item) {
					printf("%d. %s\n", number, item);
				}

			void feature1() { printf("Feature 1 selected\n"); }
			void feature2() { printf("Feature 2 selected\n"); }
			void feature3() { printf("Feature 3 selected\n"); }
			void feature4() { printf("Feature 4 selected\n"); }

			int main() {
				print_menu_item("Option 1", "Option 2", "Option 3", "Option 4", "Exit");

				int option;
				scanf("%d", &option);

				handle_option(option,
							case_option(1, feature1)
							case_option(2, feature2)
							case_option(3, feature3)
							case_option(4, feature4)
				)

				return 0;
		```
		</details>

- **_Compiler (Giai đoạn dịch NNBC sang ngôn ngữ Assembly):_** 
	-  Quá trình này compiler sẽ biên dịch từ file `.i` sang file ngôn ngữ assembly là file `.s`.
	-  Dùng lệnh `gcc -S main.i -o main.s`.
- **_Assembler (Giai đoạn dịch ngôn ngữ Assembly sang ngôn ngữ máy):_** compiler sẽ Biên dịch ngôn ngữ Assembly sang ngôn ngữ máy (0 và 1). Và tạo ra tệp tin Object `.o` 
	-  Dùng lệnh `gcc -c main.s -o main.o` để tạo ra file ".o" 
- có thể tạo thành file.hex từ file.o  
`objcopy -O ihex main.o main.hex `
- objcopy: là công cụ được sử dụng để thực hiện việc chuyển đổi.
- File hex chứa thông tin về mã máy, địa chỉ bắt đầu dữ liệu, kích thước và dữ liệu của chương trình, và thường được sử dụng để nạp chương trình vào bộ nhớ của thiết bị nhúng.


- **_Linker (Giải đoạn liên kết):_** 
	- 1 hoặc nhiều file.o sẽ được compiler liên kết lại 1 File  `.exe`.
	- File này để hệ điều hành chạy
	- Dùng lệnh `gcc  main.o -o filename` để tạo ra tệp thực thi .
  </details>

<details>
  <summary><h2>Macro và Hàm </h2></summary>

    #ifndef value 

        value(leybel): được khởi tạo với một giá trị

        ifndef(if not define): kiểm tra value được định nghĩa hay chưa

    #endif  (đóng)

    VÀ

    #ifdef value

        ifdef: ngược lại ifndef, viết tiếp với value đã được định nghĩa

    #endif

vidu:

    #define value int_int##name;
                  char_char##name;
                  double_double##name;
    int main(){
        value(biến);
    }

=> thay vì tạo 3 biến trong macro ta có thể làm như trên.

**Macro là gì?**

 - Marco là 1 tên bất kì trỏ tới 1 khối lệnh thực hiện một chức năng nào đó.

 - Được xử lý bởi preprocessor(tiền xử lý)

 - Định nghĩa macro bằng lệnh #define

 - VD: Preprocessor khi gặp bất kỳ lời gọi SUM(first+last) nào thì thay ngay bằng
 	```C
    #define SUM(a,b)     (a+b)
	int main(){
		printf("tong a,b la %d\n",sum(1,2));
		return 0;
	}
    ```

**Hàm là gì?**
 - Function là 1 khối lệnh thực hiện một chức năng nào đó.
   ```C
   int SUM(int a,int b) {//0xc1 >>0XC7
		return a+b;
   }
	     
   int main(){
		//OX00>>0X04
		printf("tong a,b la %d\n",sum(1,2));//OXO5  //stack pointer:0X05
		printf("tong a,b la %d\n",sum(2,2));//0XO7  //program counter 0xc1
		return 0;
   }
   ```
    

### So sánh Macro, Function:
**Giống nhau** : Cả hai được sử dụng để thực hiện một chức năng nào đó và có thể nhận tham số đầu vào
**Khác nhau**:
- Macro không cần quan tâm kiểu dữ liệu của tham số đầu vào
- Function phải chỉ rõ kiểu dữ liệu của tham số đầu vào
- Macro đơn giản là chỉ thay thế đoạn code macro vào chỗ được gọi trước khi được biên dịch .Giả sử 1 macro là 1 byte được gọi 20 lần >> 20 byte trong hàm main ,20 dòng code sẽ được chèn vào trong quá trình tiền xử lí. Điều này làm tốn kich thước nhưng time xử lý ngắn hơn( chỉ copy -paste vào chương trình) .

- khi khởi tạo hàm ,RAM chỉ tốn 1 bộ nhớ cố định để lưu , Giả sử hàm được gọi 20 lần, cũng sẽ chỉ tốn 1 bộ nhớ như vậy. Nhưng khi gọi hàm có thể tốn thêm thời gian do quá trình gọi hàm và quay lại vị trí ban đầu.
</details>

<details>
  <summary><h2>Stdargt - Assert</h2></summary>

<details>
  <summary><h3>Stdargt</h3></summary>

- Cú pháp: `#include<stdarg.h>`
- Dùng để viết 1 hàm có đối số biến đổi
- Đối số biến đổi (variadic arguments) là các đối số của một hàm mà số lượng và kiểu dữ liệu của chúng không được xác định trước khi biên dịch
 một kiểu biến va_list và 3 macro  được sử dụng để lấy các tham số trong một hàm khi không cần biết có bao nhiêu tham số đầu vào
- va_list là một kiểu dữ liệu được để lưu trữ các đối số biến đổi.
	+ Bạn khai báo một biến thuộc kiểu va_list để sử dụng trong việc truy cập các đối số.
	+ Ví dụ: va_list args;
- va_start:  được sử dụng để khởi tạo một va_list để truy cập các đối số biến đổi. 
	+ Nó nhận hai giá trị: va_list và số lượng tham số do người dùng nhập
	+ Ví dụ: va_start(args, last_arg);
- va_arg:  Truy cập một đối số trong danh sách.
	+ Nó nhận hai tham số: va_list và kiểu dữ liệu của đối số cần lấy
	+ Nó trả về giá trị của đối số và di chuyển va_list đến đối số tiếp theo
	+ Ví dụ: double val = va_arg(args, double);
- va_end: Kết thúc việc truy cập vào các đối số biến đổi,Nó nhận một tham số là va_list
	+ Ví dụ: va_end(args);

<details>
<summary>Ví dụ:</summary>

```C
#include <stdio.h>
#include <stdarg.h>

void example(int count, ...) {
    va_list args;
    va_start(args, count);
    
    // Lấy giá trị của đối số biến đổi thứ nhất
    int value1 = va_arg(args, int);
    printf("Value 1: %d\n", value1);
    
    // Lấy giá trị của đối số biến đổi thứ hai
    int value2 = va_arg(args, int);
    printf("Value 2: %d\n", value2);

    // Lấy giá trị của đối số biến đổi thứ ba
    int value3 = va_arg(args, int);
    printf("Value 3: %d\n", value3);

    // Lấy giá trị của đối số biến đổi thứ tư
    int value4 = va_arg(args, int);
    printf("Value 4: %d\n", value4);

    va_end(args);
}

int main() {
    example(4, 1, 2, 3, 4);
    return 0;
}


```

</details>

<details>
<summary>Ví dụ 2:</summary>

```C++
#include <stdio.h>
#include <stdarg.h>


typedef struct Data
{
    int x;
    double y;
} Data;

void display(int count, ...) {

    va_list args;

    va_start(args, count);

    int result = 0;

    for (int i = 0; i < count; i++)
    {
        Data tmp = va_arg(args,Data);
        printf("Data.x at %d is: %d\n", i,tmp.x);
        printf("Data.y at %d is: %f\n", i,tmp.y);
    }
   

    va_end(args);


}

int main() {


    display(3, (Data){2,5.0} , (Data){10,57.0}, (Data){29,36.0});
    return 0;
}

```
</details>
<details>
<summary>Ví dụ 3:</summary>

- Bài toán thực tế, làm sao viết 1 hàm chung , để phù hợp với bất kỳ số lượng tham số đầu vào.
- cảm biến độ ẩm 2 tham số , nhiệt độ 3 tham số >> cần 1 hàm phù hợp 

```C
#include <stdio.h>
#include <stdarg.h>

typedef enum {
    TEMPERATURE_SENSOR,
    PRESSURE_SENSOR
} SensorType;// đầu tiên định nghĩa 1 enum

void processSensorData(SensorType type, ...) {
    va_list args;
    va_start(args, type);

    switch (type) {
        case TEMPERATURE_SENSOR: {// khi có bài toán lựa chọn thì dùng switch..case
            int numArgs = va_arg(args, int);
            int sensorId = va_arg(args, int);
            float temperature = va_arg(args, double); // float được promote thành double
            printf("Temperature Sensor ID: %d, Reading: %.2f degrees\n", sensorId, temperature);
            if (numArgs > 2) {
                // Xử lý thêm tham số nếu có
                char* additionalInfo = va_arg(args, char*);
                printf("Additional Info: %s\n", additionalInfo);
            }
            break;
        }
        case PRESSURE_SENSOR: {
            int numArgs = va_arg(args, int);
            int sensorId = va_arg(args, int);
            int pressure = va_arg(args, int);
            printf("Pressure Sensor ID: %d, Reading: %d Pa\n", sensorId, pressure);
            if (numArgs > 2) {
                // Xử lý thêm tham số nếu có
                char* unit = va_arg(args, char*);
                printf("Unit: %s\n", unit);
            }
            break;
        }
    }

    va_end(args);
}

int main() {
    processSensorData(TEMPERATURE_SENSOR, 3, 1, 36.5, "Room Temperature");
    processSensorData(PRESSURE_SENSOR, 2, 2, 101325);
    return 0;
}

```
</details>
  </details>

  <details>
  <summary><h3>Assert</h3></summary>
  
  - Cung cấp macro assert. 
	- Macro này được sử dụng để kiểm tra một điều kiện. 
	- Nếu điều kiện đúng (true), không có gì xảy ra và chương trình tiếp tục thực thi.
	- Nếu điều kiện sai (false), chương trình dừng lại và thông báo một thông điệp lỗi.
	- Dùng trong debug, dùng #define NDEBUG để tắt debug
	- Tóm lại, assert thường được sử dụng để kiểm tra điều kiện và kết thúc chương trình khi có lỗi 
<details>
<summary>Ví dụ:</summary>

```C
#include <stdio.h>
#include <assert.h>
int main() {   
	int x = 5;    
	assert(x == 5);    // Chương trình sẽ tiếp tục thực thi nếu điều kiện là đúng.
	printf("X is: %d", x);  
	return 0;
}

```
</details>

-Thông thường trong thực tế sẽ code:
<details>
<summary>Ví dụ:</summary>

```C
#define LOG(condition, cmd) assert(condition && #cmd);
int main{
	int x=0;
	LOG(x>5,x phai lon hon 5);
}
```

Hoặc

```C
#include <assert.h>
#define ASSERT_IN_RANGE(val, min, max) assert((val) >= (min) && (val) <= (max))

void setLevel(int level) {
    ASSERT_IN_RANGE(level, 1, 31);
    // Thiết lập cấp độ
}
int main(){
	int x=45;
	int day =5;
	ASSERT_IN_RANGE	(day,0,31);// day <31 thì sẽ thực hiện code tiếp theo
	//sai thì thông báo 
	printf("day bang %d\n",day);

}

```
  </details>
    </details>
    </details>

<details>
  <summary><h2>VARIABLE </h2></summary>

- Biến cục bộ là biến tồn tại trong các hàm :Hàm main() , hàm con.Biến cục bộ sẽ được lưu vào vùng nhớ stack, thu hồi khi kết thúc hàm. 
- Biến toàn cục là các biến được khai báo ở bên ngoài tất cả các hàm , Biến toàn cục tồn tại cho tới khi chương trình kết thúc.

Sử dụng thư viện **stdint.h** để dùng các kiểu dữ liêu uint_t (kích thước của biến)

        uint8_t = 1 byte
        uint16_t = 2 byte

<details>
  <summary><h3>Static </h3></summary>

- Biến cục bộ bình thường: sau khi gọi thì biến khởi tạo giá trị biến và sẽ thu hồi địa chỉ trên bộ nhớ Ram khi chương trình kết thúc khỏi biến đó, lần thứ hai gọi biến thì chương trình sẽ khởi tạo lại giá trị biến từ đầu và có thể giống hoặc không địa chỉ trên bộ nhớ so với lần gọi đầu.

**vidu:**      

            uint8_t temp = 0;
            printf("temp: %d\n", temp);
            temp++;

- Biến cục bộ dùng static: khi gọi thì biến khởi tạo giá trị chỉ một lần và cố định địa chỉ giá trị đó tồn tại hết vòng đời của chương trình(sau khi kết thúc thì mới thu hồi lại địa chỉ trên bộ nhớ Ram), và lần gọi thứ hai của biến thì giá trị sẽ được tiếp tục.

**vidu:**   

            static uint8_t temp = 0;
            printf("temp: %d\n", temp);
            temp++;

- Biến toàn cục static chỉ có giá trị trong phạm vi file chứa nó, không extern sang file khác được còn biến cục bộ thì được.

### Khác nhau của static cục bộ và static toàn cục:

**Biến static cục bộ:** 
- Khi 1 biến cục bộ được khai báo với từ khóa static. Biến sẽ chỉ được khởi tạo 1 lần duy nhất và tồn tại suốt thời gian chạy chương trình. 
- Giá trị của nó không bị mất đi ngay cả khi kết thúc hàm
- Biến static sẽ lưu vào vùng nhớ Data/ Bss, được giải phóng khi kết thúc chương trình.

- Ví dụ:

```C
		#include <stdio.h>
		void printMessage() {
		static int count = 0;
		// Tăng giá trị biến mỗi lần hàm được gọi
		count++;
		printf("Count: %d\n", count);
		}

		int main() {
		// Gọi hàm có sử dụng biến static
		printMessage();//
		printMessage();

		return 0;
		}// KQ:Count: 1,Count: 2

```

**Biến static toàn cục:**  
- Biến toàn cục static sẽ chỉ có thể được truy cập và sử dụng trong File khai báo nó, các File khác không có cách nào truy cập được.Nghĩa là `extern` không dùng được
- Ví dụ:globalStaticVar được khai báo là static và nằm trong file "File1.c". Do đó, bạn không thể trực tiếp truy cập nó từ file "File2.c", bằng extern int globalStaticVar; trong File2.c, chương trình sẽ không biên dịch được và thông báo lỗi.
  </details>

  <details>
  <summary><h3>Extern </h3></summary>
  - Extern trước 1 biến để thông báo biến này đã được khai báo ở một nơi file khác.
- Biến extern không tạo ra bộ nhớ mới cho biến , tiết kiệm dung lượng chương trình
- Biến được tham chiếu phải được khai báo toàn cục.
- Lưu ý: khi sử dụng extern, không được khai báo giá trị ban đầu cho biến

- ta có file1 có biến int a và file2. khi ta muốn sử dụng int a của file1 vào file2 thì dùng extern (extern int a)

- không được khởi tạo, giá trị biến tại file extern chỉ được gọi, chỉ được ở file (test)

- vì runcode chỉ build được một file duy nhất nên ta dùng:

            (gcc file1.c file2.c -o file1) file1 là file dùng extern.

            gcc 4_3_extern.c 4_2_test.c -o 4_3_extern 

            ./4_3_extern (./file1)

 <details>
<summary>Ví dụ</summary>

- File 1 ta khai báo

```C
int GlobalVariable = 0; // implicit definition 
void SomeFunction(); // function prototype (declaration) 
int main() 
{ 
  GlobalVariable = 1; 
  SomeFunction(); 
  return 0; 
}
```
- File 2, chúng ta extern biến đó để sử dụng

```C
extern int GlobalVariable; // implicit definition 
void SomeFunction(); // function prototype (declaration) 
int main() 
{ 
  GlobalVariable = 1; 
  SomeFunction(); 
  return 0; 
}; 
```
 </details>

  </details>

  <details>
  <summary><h3>Register </h3></summary>

  - ALU(bộ xử lý tính toán), Register (thanh ghi), RAM (cấu trúc vi xử lý gồm RAM và Register)

    ![Register](https://github.com/langvt/C_Cpp_Advanced/blob/main/images/bai4_Register.png?raw=true)

    **vidu**: int a = 5; a++;
  
    ![Register](https://github.com/langvt/C_Cpp_Advanced/blob/main/images/bai4_Register1.png?raw=true)

    - vì Register có bộ nhớ giới hạn nên chỉ ưu tiên dùng Register cho những biến cần tốc độ xử lý cao, còn lại tất cả được lưu trên RAM.

  - Từ khóa register trước 1 biến để thông báo biến này sẽ lưu thanh ghi của CPU, chứ không phải vào RAM. 
- Do lưu trong thanh ghi nên tốc độ xử lý sẽ nhanh hơn.
    `register int counter = 0;`
- Hạn chế dùng register vì thanh ghi có giới hạn (32 bit là 4 byte , 64 bit là 8 byte ) >> chỉ lưu những biến quan trọng , cần tính toán nhanh
- Giải thích :Nếu khai báo biến thông thường để tính toán không có từ khóa register , thực hiện một phép tính thì cần có 3 bước.
	- Ví dụ: `int a = 6.Ví dụ :a có địa chỉ là 0X01,  a=a+4`
	- B1:Lưu địa chỉ và giá trị của biến vào bộ nhớ RAM : `0X01=6;` 
	- B2:Sau đó chuyển từ Ram qua thanh ghi(register)
	- B3:Từ register chuyển qua ALU (Arithmetic Logic Unit) ,để tính toán.Sau khi tính toán xong thì lại chuyển ngược về register>> về RAM


  </details>

  <details>
  <summary><h3>Volatile </h3></summary>

    - Thông báo cho trình biên dịch không tối ưu biến này,nếu tối ưu thì sẽ không đúng kết quả của người code.

    - Sử dụng volatile với biến có giá trị thay đổi từ bên ngoài , liên tục và giống nhau.Nếu không có volatile, compiler sẽ hiểu rằng các biến như vậy dường như không thay đổi giá trị nên compiler có xu hướng loại bỏ để có thể tối ưu kích cỡ file code .

    - Ví dụ:
```C
   	int main() {
    volatile int sensorValue;

    while (1) {
        // Đọc giá trị từ cảm biến (sensor)
        sensorValue = readSensor();

        // Xử lý giá trị cảm biến
        processSensorValue(sensorValue);
    }

    return 0;
}
```
  </details>

  </details>


  <details>
  <summary><h2>Phân vùng bộ nhớ trên RAM, cấp phát bộ nhớ động</h2></summary>

   - Chương trình main.exe trên window  hoặc main.hex với VĐK (lưu ở bộ nhớ SSD hoặc FLASH). 
- Khi nhấn run chương trình trên window hoặc cấp nguồn cho vi điều khiển thì những chương trình này sẽ được copy vào bộ nhớ RAM để thực thi.


| Stack |
|:-----:|
|   ↓   |
|   ↑   |	
|  Heap |
|  Bss(Uninitialized data)  |
|  Data(Initialized data)   |
|  Text |


**vidu**: 

```C
    int a; (.bss)
    int b = 42; (.data)

    void main(void)  (.text)
    {
        int c;
        a=10;
        cong(a,b);
    }

 ```
==> sections

  <details>
  <summary><h3>Phân vùng bộ nhớ </h3></summary>

Phân vùng nhớ gồm hai vùng nhớ là Flash và RAM:

    Flash: khi mất nguồn điện thì vẫn lưu các chương trình
    RAM : Độ truy xuất nhanh nhưng khi mất nguồn điện thì sẽ mất hết các chương trình đang chạy

Trong bộ nhớ RAM sẽ có 5 phân vùng nhớ: text, data, bss, heap, stack

- ***Text (text segment):*** Quyền truy cập chỉ có thể Read( không thay đổi)
	- Lưu các hằng số :`const int x =2` 
	- Kích thước là cố định
	- Nó chưa lệnh thực thi :Mã assembly...
    - Hằng số sẽ được lưu ở phân vùng text (.rodata);

    **vidu**

        void main(void)  (.text)
        {
            int c;
            a=10;
            cong(a,b);
        }
 - ***Data (Initialized Data segment):*** Quyền truy cập Read-Write
	- Chứa biến toàn cục đã dc khởi tạo hoặc biến static khác 0:`int a=1, int b=2;`
	- Được giải phóng khi kết thúc chương trình
	- Kích thước có thể thay đổi

     **vidu**: 

            int global = 100;
            static int = 100;
            
        nằm trong hàm main nhưng khai báo với biến static

            int main(){
            static int = 100;
            }

    **Chú ý**: căn cứ giá trị gán ở lần đầu tiên để phân vùng

        vidu: static uint8_t test = 21; sau có thay đổi giá trị 21 = 0 thì vẫn được lưu ở Data

- ***Bss (uninitialized Data segment):*** Quyền truy cập Read-Write
	- Chứa biến toàn cục chưa khởi tạo, hoặc bằng 0:`int a=0, int b;`
	- Các biến static bằng 0 hoặc chưa khởi tạo
	- Được giải phóng khi kết thúc chương trình
	- Kích thước có thể thay đổi

    **vidu:** 

            int global;
            static int = 0;


    **Chú ý:** căn cứ giá trị gán ở lần đầu tiên để phân vùng

        vidu: static uint8_t test = 0; sau có thay đổi giá trị 0 = 21 thì vẫn được lưu ở bss

- ***Stack (Automatic Variable Storage_cấp phát bộ nhớ tự động):*** Quyền truy cập là Read-Write.
	- lưu trữ các biến cục bộ.
    - Được sử dụng cấp phát cho biến local(cục bộ):
        + input parameter
        + Được khai báo bên trong một block code '{'và'}' (vidu ham main(){this code})
	- Các tham số truyền vào và các giá trị trả về từ hàm.
	- Hàm main cũng ở vùng stack
	- Sẽ được giải phóng khi ra khỏi hàm
	- Kích thước cố định: phụ thuộc vào hệ điều hành, đối với Windows thường là 1MB, Linux là 8MB.

- ***Heap (Dynamic Memory allocation_cấp phát bộ nhớ động):*** Quyền truy cập là Read-Write.
- Được sử dụng để cấp phát bộ nhớ động như: Malloc, Calloc,...
- Kích thước không cố định.
- Sẽ được giải phóng khi gọi hàm free,...

  </details>

  <details>
  <summary><h3>So sánh Stack và Heap?</h3></summary>

	- Bộ nhớ: Bộ nhớ Heap và bộ nhớ Stack bản chất đều cùng là vùng nhớ được tạo ra và lưu trữ trong RAM khi chương trình được thực thi.
		- Stack được dùng để lưu trữ các biến cục bộ trong hàm, tham số truyền vào... Truy cập vào bộ nhớ này rất nhanh và được thực thi khi chương trình được biên dịch.
		- Heap được dùng để lưu trữ vùng nhớ cho những biến con trỏ được cấp phát động bởi các hàm malloc - calloc - realloc (trong C)
	- Kích thước vùng nhớ:
		- Stack: kích thước của bộ nhớ Stack là cố định, tùy thuộc vào từng hệ điều hành, ví dụ hệ điều hành Windows là 1 MB, hệ điều hành Linux là 8 MB (lưu ý là con số có thể khác tùy thuộc vào kiến trúc hệ điều hành của bạn).
		- Heap: kích thước của bộ nhớ Heap là không cố định, có thể tăng giảm do đó đáp ứng được nhu cầu lưu trữ dữ liệu của chương trình.

    </details>

    <details>
  <summary><h3>Các cách sử dụng malloc, calloc, realloc, free</h3></summary>

	- ***Malloc:*** Cấp phát bộ nhớ động mỗi phần tử, không khởi tạo giá trị, trả về con trỏ NULL khi cấp phát thành công.
	- ***Calloc:*** Cấp phát bộ nhớ động và khởi tạo cho các phần tử là 0, trả về con trỏ NULL khi cấp phát thành công.
	- ***Realloc:*** Thay đổi kích thước bộ nhớ của bộ nhớ đã được cấp phát trước đó của Malloc và Calloc, trả về con trỏ NULL khi thay đổi thành công.
	- Vậy `Malloc` sẽ nhanh hơn `Calloc`
	- Ví dụ:

	```C
	int main() {
    int *arr_malloc, *arr_calloc;
    size_t size = 5;

    // Sử dụng malloc
    arr_malloc = (int*)malloc(size * sizeof(int));

    // Sử dụng calloc
    arr_calloc = (int*)calloc(size, sizeof(int));

    // Sử dụng Realloc
	arr_malloc = (int*)realloc(arr_malloc, sizeof(int) * 7); // size arr_malloc lúc này là 7


    // Giải phóng bộ nhớ
    free(arr_malloc);
    free(arr_calloc);

    return 0;
	}
	```
<details>
<summary>Ví dụ:</summary>

```C
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{  
    int soluongkytu = 0;
    char* ten = (char*) malloc(sizeof(char) * soluongkytu)
    for (int i = 0; i < 3; i++)
    {
        printf("Nhap so luong ky tu trong ten: \n");
        scanf("%d", &soluongkytu);
        ten = realloc(ten, sizeof(char) * soluongkytu);
        printf("Nhap ten cua ban: \n");
        scanf("%s", ten);
        printf("Hello %s\n", ten);
    }

}

```
</details>

</details>

  <details>
  <summary><h3>Đặc điểm vùng nhớ</h3></summary>

	- Stack: 
		- vùng nhớ Stack được quản lý bởi hệ điều hành, 
		- Dữ liệu được lưu trong Stack sẽ tự động hủy khi hàm thực hiện xong công việc của mình.
	- Heap: k
		- Kích thước của bộ nhớ Heap là không cố định, có thể tăng giảm do đó đáp ứng được nhu cầu lưu trữ dữ liệu ,
		- Dữ liệu trong Heap sẽ không bị hủy khi hàm thực hiện xong, điều đó có nghĩa bạn phải tự tay hủy vùng nhớ bằng câu lệnh free (trong C), và delete hoặc delete [] (trong C++), nếu không sẽ xảy ra hiện tượng rò rỉ bộ nhớ. 
### Lưu ý: 
- Việc tự động dọn vùng nhớ còn tùy thuộc vào trình biên dịch trung gian.
- Vấn đề lỗi xảy ra đối với vùng nhớ Stack: Bởi vì bộ nhớ Stack cố định nên nếu chương trình bạn sử dụng quá nhiều bộ nhớ vượt quá khả năng lưu trữ của Stack chắc chắn sẽ xảy ra tình trạng tràn bộ nhớ Stack (Stack overflow), các trường hợp xảy ra như bạn khởi tạo quá nhiều biến cục bộ, hàm đệ quy vô hạn,..
	- Ví dụ về tràn bộ nhớ stack với hàm đệ quy vô hạn:
	```C
	int foo(int x){
		printf("De quy khong gioi han\n");
		return foo(x);
	}
	```
- Vấn đề lỗi xảy ra đối với vùng nhớ Heap: Nếu bạn liên tục cấp phát vùng nhớ mà không giải phóng thì sẽ bị lỗi tràn vùng nhớ Heap (Heap overflow). Nếu bạn khởi tạo một vùng nhớ quá lớn mà vùng nhớ Heap không thể lưu trữ một lần được sẽ bị lỗi khởi tạo vùng nhớ Heap thất bại.
	- Ví dụ trường hợp khởi tạo vùng nhớ Heap quá lớn:
	```C 
	int *A = (int *)malloc(18446744073709551615); 
	```

- ***Realloc:*** Thay đổi kích thước bộ nhớ của bộ nhớ đã được cấp phát trước đó của Malloc và Calloc, trả về con trỏ NULL khi thay đổi thành công
```C
void* realloc(void* ptr, size_t size);
```
- ***Free:*** Giải phóng bộ nhớ đã được cấp phát bằng Malloc, Calloc, Realloc sau khi sử dụng xong, không có trả về
```C
void free(void* ptr);
```

</details>

  <details>
  <summary><h3>Khác nhau của static cục bộ và static toàn cục</h3></summary>


- Biến static cục bộ: Khi 1 biến cục bộ được khai báo với từ khóa static. Biến sẽ chỉ được khởi tạo 1 lần duy nhất và tồn tại suốt thời gian chạy chương trình. Giá trị của nó không bị mất đi ngay cả khi kết thúc hàm. Tuy nhiên khác với biến toàn cục có thể gọi trong tất cả mọi nơi trong chương trình, thì biến cục bộ static chỉ có thể được gọi trong nội bộ hàm khởi tạo ra nó. Mỗi lần hàm được gọi, giá trị của biến chính bằng giá trị tại lần gần nhất hàm được gọi.Biến static sẽ lưu vào vùng nhớ Data/ Bss, được giải phóng khi kết thúc chương trình.

- Ví dụ:

```C
 	#include <stdio.h>
	void printMessage() {
    static int count = 0;
    // Tăng giá trị biến mỗi lần hàm được gọi
    count++;
    printf("Count: %d\n", count);
	}

	int main() {
    // Gọi hàm có sử dụng biến static
    printMessage();//
    printMessage();

    return 0;
	}// KQ:Count: 1,Count: 2

```

- Biến static toàn cục: Biến toàn cục static sẽ chỉ có thể được truy cập và sử dụng trong File khai báo nó, các File khác không có cách nào truy cập được.
- Ví dụ:globalStaticVar được khai báo là static và nằm trong file "File1.c". Do đó, bạn không thể trực tiếp truy cập nó từ file "File2.c", bằng extern int globalStaticVar; trong File2.c, chương trình sẽ không biên dịch được và thông báo lỗi.
- Biến cục bộ: Biến cục bộ sẽ được lưu vào vùng nhớ stack, thu hồi khi kết thúc hàm cục bộ. 

</details>
</details>



<details>
<summary><h2>Struct _ Union </h2></summary>

  <details>
  <summary><h3>Struct </h3></summary>

- Là kiểu dữ liệu do người dùng tự định nghĩa giống như int, double
- Sử dụng typedef để định nghĩa ngắn gọn lại

**vidu:** 


            typedef struct
            {
                int ngay;
                int thang;
                int nam;
            }typeDate;

- Struct là một kiểu dữ liệu chứa nhiều kiểu dữ liệu khác trong nó , kích thước của struct bằng kích thước các thành viên bên trong + phần padding.
- Struct padding :
	+ Data alignment:Việc thao tác các biến có địa chỉ liền kề là 1 số lẻ là phức tạp , nên CPU luôn thao tác các địa chỉ là số chẵn >> Data alignment là việc 	sắp xếp data sao cho địa chỉ của các biến luôn là số chẵn và phù hợp với hệ thống.
	+ Data padding: là thêm các vùng nhớ đệm để có địa chỉ chẵn

## Kích thước của Struct (sizeof)

- căn cứ vào member có kích thước lớn nhất để lấy kích thước lớn nhất cho từng member sau mỗi lần quét các member đó.

    Ta có kích thước byte lớn nhất của các lần quét là là Z byte

    + Quét "lần 1" có X byte: gồm có A byte sử dụng và B byte bộ nhớ đệm trong Z byte.
    
    + Quét "lần 2" có Y byte, nhưng so sánh kích thước của B byte bộ nhớ đệm lần quét 1 và kích thước lần quét 2.

        * Nếu kích thước lần quét 2 nhỏ hơn kích thước Zbyte bộ nhớ đệm lần quét 1 thì ta đưa "lần 2" vào sử dụng bộ nhớ đệm của lần quét 1.
        * Nếu kích thước lần quét 2 lớn hơn kích thước Zbyte bộ nhớ đệm lần quét 1 thì phải sử dụng kích thước lần quét 2 là Z byte.
    + Các lần quét tiếp theo tương tự
## Ví dụ:

![Struct](https://github.com/langvt/C_Cpp_Advanced/blob/main/images/Struct1.png?raw=true)
-   Tổng Example là 8 byte , 7 byte dữ liệu + 1 byte trống 

![Struct](https://github.com/langvt/C_Cpp_Advanced/blob/main/images/struct2.png?raw=true)
- Tổng Example là 12 byte ,  7 byte dữ liệu + 5 byte trống

![Struct](https://github.com/langvt/C_Cpp_Advanced/blob/main/images/struct3.png?raw=true)
- Tổng Example là 24 byte ,cơ bản là tốn time tính

##Và mục đích tính toán struct,để tối ưu bộ nhớ,nếu sắp xếp các phần tử không hợp lý sẽ tốn bộ nhớ.

  </details>

<details>
  <summary><h3>Union </h3></summary>

- Giống như Struct, Union cũng là kiểu dữ liệu do ngườ dùng tự định nghĩa. 
- Giá trị của các biến trong Union đều giống nhau và bằng giá trị của biến được khởi tạo cuối cùng vì các biến trong Union đều cùng một địa chỉ nên khi khởi tạo thì giá trị sau sẽ ghi đè lên giá trị trước.
- kích thước của Union bằng kích thước thành viên lớn nhất và cùng 1 vùng nhớ.
- cho phép lưu trữ các biến khác nhau trong cùng một vị trí bộ nhớ. Khi một giá trị mới được gán cho union, giá trị trước đó được ghi đè. Điều này có nghĩa là union chỉ lưu trữ một giá trị duy nhất tại một thời điểm.

<details>
<summary>Ví dụ </summary>

                #include <stdio.h>
                #include <stdint.h>
                #include <string.h>

                typedef union 
                {

                uint8_t var1[5]; // char
                uint16_t var2[2]; // long

                }typeData;

                int main(int argc, char const *argv[])
                {
                    typeData data ;

                    for(int i = 0; i < 5; i++){
                        data.var1[i] = i; // 0 1 2 3 4
                    }

                    for(int i = 0; i < 2; i++){
                        data.var2[i] = 2*i ;  // 0 2
                    }

                    for(int i = 0; i < 5 ; i++){
                        printf("test1: %d\n", data.var1[i]);
                    }
                
                    return 0;
                }


kết quả là: 0 0 2 0 4
- var1 có kết quả là: 0 1 2 3 4 (var1 có giá trị 1 byte nên mỗi ô là một giá trị i)
- var2 có kết quả là: 0 0 2 0 (vì var 2 có giá trị là 2 byte nên ô lưu trữ đầu tiên là giá trị i và ô lưu trữ thứ 2 là giá trị 0)
- do cùng một địa chỉ nên var2 sẽ ghi đè lên var1 sau đó var2 = var1 
- do đó kết quả cuối cùng là: 0 0 2 0 4

</details>

<details>
<summary>Ví dụ </summary>

```c
#include <stdio.h>

union Data {
    int i;
    float f;
    char str[20];
};

int main() {
    union Data data;

    data.i = 10;  // Gán giá trị cho thành viên int
    printf("data.i: %d\n", data.i);  // In ra giá trị của thành viên int

    data.f = 220.5;  // Gán giá trị cho thành viên float
    printf("data.f: %f\n", data.f);  // In ra giá trị của thành viên float

    // Truy cập thành viên int sau khi đã gán giá trị cho thành viên float
    printf("data.i: %d\n", data.i);  // Giá trị này không còn chính xác do đã bị thay đổi

    return 0;
}

```

</details>

![union](./images/Union.PNG)
- Tổng Example là 20 byte , thằng nào lớn nhất thì lấy thằng đó

#### Mục đích sử dụng  Union ,để tiết kiệm bộ nhớ ,vì 1 thời điểm chỉ có thể sử dụng 1 member. 
- Ứng dụng đọc 1 cảm biến trong nhiều cảm biến.
- Nếu cùng 1 mục đích mà sử dụng struct sẽ tốn nhiều dung lượng hơn.

![union](./images/Union1.PNG)
- Ví dụ trên nếu dùng struct thì 8 byte , trong khi union chỉ 4 byte

  </details>

### TỔng kết
Struct:
- là kiểu dữ liệu do người dùng tự định nghĩa;
- Kích thước là tổng các member cộng lại (byte sử dụng và byte bộ nhớ đệm);
Mỗi member của struct đều có địa chỉ riêng nên khi thay đổi giá trị của một member thì không ảnh hưởng đến member khác.

Union:
- là kiểu dữ liệu do người dùng tự định nghĩa;
- Kích thước của union sẽ là kích thước của member lớn nhất;
Các member trong Union đều dùng chung một địa chỉ nên khi thay đổi một giá trị member thì sẽ ảnh hưởng đến giá trị các member khác

  </details>



<details>
  <summary><h2>Goto_EXIT_setjmp</h2></summary>

<details>
  <summary><h3>Goto</h3></summary>
    - Cung cấp 1 bước nhảy từ 'goto' đến một câu lệnh có label  đã được đặt trước đó trong cùng một hàm.
    - label có thể là một văn bản thuần túy trừ từ khóa C, label có thể được đặt ở bất kì đâu trong chương trình có thể ở trên hoặc dưới câu lệnh 'goto'.

<details>
<summary>Ví dụ</summary>

```C
#include <stdio.h>
int main() {    
	int i = 0;   // Đặt nhãn    start        
	if (i >= 5) {           
		goto end;  // Chuyển control đến nhãn "end"       
		}       
		printf("%d ", i);        
		i++;        
		goto start;  // Chuyển control đến nhãn "start"    		 
		end: // Nhãn "end"       
		printf("\n");
		return 0;
	}
```

</details>
</details>

  <details>
  <summary><h3>Exit</h3></summary>
- Sử dụng thư viện stdlib.h để dùng Exit
- Exit: dừng lại chương trình chứ không thoát khỏi
  </details>

<details>
  <summary><h3>setjmp</h3></summary>

- `setjmp.h` là một thư viện trong ngôn ngữ lập trình C, chứa các hàm setjmp và longjmp được sử dụng để xử lý các tình huống ngoại lệ.
- Khi điều kiện là sai, chúng không dừng chương trình lại như assert, mà thay vào đó chúng tạo ra một cơ hội để nhảy đến một điểm nhảy trước đó đã được đánh dấu bởi setjmp
- `setjmp` sẽ lưu điểm đánh dấu chương trình ngoại lệ .
- `longjmp` được sử dụng để nhảy đến một điểm  đã được đánh dấu bởi setjmp.

- Sử dụng thư viện setjmp.h để dùng setjum
- sử dụng setjmp với TRY CATCH THROW để khi chương trình có lỗi thì mọi sẽ dừng lại đê ưu tiên xử lý lỗi trước và trỏ con trỏ đến vùng lỗi để xử lý (rất phức tạp khi không dùng setjmp ở các vòng lặp)

vidu: 

    #include <stdio.h>

    #include <stdlib.h>

    #include <setjmp.h>

    int main(int argc, char const *argv[])
    {
        // khởi tạo biến jmp_buf
        jmp_buf jumb;
        int i = setjmp(jumb); //  có giá trị = 0

    printf("i: %d\n",i); // in ra gia tri 0

    if (i!= 0) // khong co gia tri nao khac 0 nên khong chay qua ham if
    {
        exit(0); 
    }

    longjmp(jumb, 1);// khoi tao gán giá trị = 1

    printf("test\n"); // in ra = 1, sau do se quay lai setjmp va tra lai gia tri i= 1 khi do den exit se dung


    return 0;
    }

khi nào chương trình gặp longjmp() thì con trỏ sẽ quay ngược lại vị trí của setjmp()

<details>
<summary>TRY_CATCH_THROW</summary>

```C

#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;//jmp_buf là kiểu dữ liệu trong thư viện Setjmp.h
int exception_code;

#define TRY if ((exception_code = setjmp(buf)) == 0) 
#define CATCH(x) else if (exception_code == (x)) 
#define THROW(x) longjmp(buf, (x))


double divide(int a, int b) {
    if (b == 0) {
        THROW(1); // Mã lỗi 1 
    }
    return (double)a / b;
}

int main() {
    int a = 10;
    int b = 0;
    double result = 0.0;

    TRY {
        result = divide(a, b);
        printf("Result: %f\n", result);
    } CATCH(1) {
        printf("Error: Divide by 0!\n");
    }


    // Các xử lý khác của chương trình
    return 0;
}

### vidu2 
#include <stdio.h>

#include <stdlib.h>

#include <setjmp.h>

    jmp_buf buf;
    int check_value = 0;

    #define TRY if((check_value = setjmp(buf)) == 0)

    #define CATCH(num) else if (check_value = num)

    #define THROW(num) longjmp(buf, num)

    double thuong (int a, int b){
        if(b == 0){
            THROW(1);
        }
        return (double)a/b;
    }
int main(int argc, char const *argv[])
{

    double kq;

    TRY {
        kq = thuong (12, 0);
        printf("kq: %f\n", kq);
    }
    CATCH(1){
        printf("ERROR, mau bang 0");
    }
    
    return 0;
}

- trong chương trình trên TRY CATH THROW thực chất là cách viết các điều kiện lỗi if else bình thường: TRY là chương trình chính, CATH để in ra lỗi từng trường hợp, THROW là longjmp là để viết điều kiện lỗi
- 
 - Khi dùng TRY CATH THROW thì khi chương trình bị lỗi sẽ được ưu tiên gỡ lỗi trước, khi có lỗi thì sẽ vào CATH để in ra từng lỗi 

 - ứng dụng khi chương trình có nhiều điều kiện ngoài lề như if else, vòng lặp ..., thì viết theo kiểu TRY CATH sẽ được ưu tiên xử lý trước khi gặp lỗi 
```

  </details>
</details>
</details>


<details>
  <summary><h2>Pointer</h2></summary>

- Con trỏ (pointer) là một biến chứa địa chỉ bộ nhớ của một biến khác. Việc sử dụng con trỏ giúp chúng ta thực hiện các thao tác trên bộ nhớ một cách linh hoạt hơn.
- Thông qua con trỏ có thể thay đổi giá trị tại biến mà nó trỏ tới
- Cách khai báo:

```C
int x = 10;
int *ptr = &x;  // ptr giờ đây chứa địa chỉ của x
*ptr =5;
>> x bằng5
```

**Chú ý:**


- "*ptr" ở khai báo là **con trỏ**
- "*ptr" sử dụng ở những câu lệnh bên dưới sau khi khai báo xong là **toán tự giải tham chiếu**. truy cập vào giá trị mà con trỏ đang trỏ tới (địa chỉ cảu biến) để thay đổi giá trị của biến.

- Thông qua con trỏ có thể thay đối giá trị của biến a = 10.

    >*ptr = 100 // tương ứng với a = 100

    vì khi con trỏ (int *ptr) tham chiếu tới biến a thì toán tử giải tham chiếu (*ptr) chính là giá trị của biến a, khi thay đổi hay tăng giảm sẽ trực tiếp ảnh hưởng đến giá trị ô nhớ.

**Vidu:**

        #include <stdio.h>

        int a = 5;

        void tong(){
            printf("hello\n");
        }

        int main(int argc, char const *argv[])
        {
            int *ptr = &a;
            *ptr = 27;

            printf("dia chi cua a: %p\n", ptr);
            printf("gia tri a: %d\n", *ptr);
            printf("gia tri a: %d\n", a);

            printf("dia chi cua tong: %p\n", ptr);
            return 0;
        }


- con trỏ có địa chỉ là 0x00 và giá trị là 0 được gọi là con trỏ NULL.
- khi mà không còn nhu cầu sử dụng con trỏ đã khai báo thì gán con trỏ đó bằng NULL:
    > int *ptr = NULL;

- Kích thước của con trỏ phụ thuộc vào kiến trúc máy tính và trình biên dịch.
- `Môi trường Windows 32 bit: 4 bytes`
- `Môi trường Windows 64 bit: 8 bytes`

```C
int main()
{
    int *ptr;
    printf("Size of pointer: %d bytes\n", sizeof(ptr));    
    return 0;

}

```
- Ứng dụng để truyền tham trị .
### vidu: 
```C
#include <stdio.h>

// Hàm swap: Đổi giá trị của hai biến sử dụng con trỏ
void swap(int *a, int *b)
{
    int tmp = *a;   // Lưu giá trị của biến a vào biến tạm thời tmp
    *a = *b;        // Gán giá trị của biến b cho biến a
    *b = tmp;       // Gán giá trị của biến tạm thời tmp (ban đầu là giá trị của a) cho biến b
}

// Hàm main: Hàm chính của chương trình
int main()
{
    int a = 10, b = 20; // Khai báo và khởi tạo hai biến a và b

    swap(&a, &b);       // Gọi hàm swap để đổi giá trị của a và b

    // In ra giá trị của a và b sau khi đã đổi giá trị
    printf("value a is: %d\n", a);
    printf("value b is: %d\n", b);

    return 0; // Kết thúc chương trình
}

```

  <details>
  <summary><h3>Con trỏ hàm</h3></summary>

- Hàm (function) bản chất là 1 địa chỉ vùng nhớ
- con trỏ hàm là một biến chứa địa chỉ của một hàm.`void (*ptr)();`
- khi khởi tạo xong thì phải gán địa chỉ của hàm cho con trỏ hàm.`ptr = add;`
- sau khi gán rồi có thể gọi hàm thông qua con trỏ hàm  .`ptr();`
- Cú pháp:
`kiểu dữ liệu (*tên con trỏ hàm)(kieu du liêu1, kieu du liêu2)` 
- kiểu dữ liệu trùng với kiểu dữ liệu của hàm trỏ tới.
- Nếu cần truyền tham số thì kiểu dữ liệu 1 ,2 trùng với hàm truyền vào.
- Điều này cho phép truyền một hàm cụ thể vào một hàm khác 
- Có thể thông qua mảng để lưu giá trị các hàm mà nó trỏ tới
- con trỏ đặc biệt: là con trỏ có thể lưu các giá trị địa chỉ khác kiểu dữ liệu.
    >void *ptr = &a
 <details>
<summary>Ví dụ:</summary>

```C
#include <stdio.h>

// Hàm mẫu
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int main() {
    // Khai báo con trỏ hàm với cú pháp: <kiểu dữ liệu trả về> (*<tên con trỏ>)(<kiểu dữ liệu đối số 1>, <kiểu dữ liệu đối số 2>, ...)
    int (*operation)(int, int);

    // Gán địa chỉ của hàm add cho con trỏ hàm
    operation = add;

    // Sử dụng con trỏ hàm để gọi hàm add
    printf("Result: %d\n", operation(5, 3)); // In ra: Result: 8

    // Gán địa chỉ của hàm subtract cho con trỏ hàm
    operation = subtract;

    // Sử dụng con trỏ hàm để gọi hàm subtract
    printf("Result: %d\n", operation(5, 3)); // In ra: Result: 2

    return 0;
}

```
</details>
</details>


  <details>
  <summary><h3>Hàm con trỏ</h3></summary>
- Hàm con trỏ là một hàm mà tham số của nó là một con trỏ hàm.
- Điều này cho phép bạn truyền một hàm cụ thể vào một hàm khác để thực hiện các tác vụ động linh hoạt
<details>
<summary>Ví dụ:</summary>

```C
#include <stdio.h>
// Hàm con trỏ làm tham số cho một hàm khác
void processNumbers(int (*operation)(int, int), int a, int b) {
    int result = operation(a, b);
    printf("Result: %d\n", result);
}

// Hàm mẫu 1
int add(int a, int b) {z
    return a + b;
}

int main() {
    int a = 10, b = 5;
    processNumbers(add, a, b);
    

    return 0;
}
```
</details>
</details>

  <details>
  <summary><h3>Con trỏ void.</h3></summary>
- Void Pointer  là một kiểu đặc biệt của con trỏ ,nó có thể trỏ đến bất kỳ địa chỉ nào mà không cần biết tới kiểu dữ liệu của giá trị tại địa chỉ đó.
- Cách ép kiểu dữ liệu từ con trỏ Void:`(int*)(ptr)` đang ép về kiểu int.
- Dùng trong bài toán , nhiều kiểu dữ liệu mà không muốn dùng nhiều loại con trỏ trỏ tới chúng .
- Trong ví dụ bên dưới, con trỏ ptr trỏ tới tất cả các biến.
<details>
<summary>Ví dụ:</summary>

```C
#include <stdio.h>
#include <stdlib.h>

int sum(int a, int b)
{
    return a+b;
}

int main() {
   
    char array[] = "Hello";
    int value = 5;
    double test = 15.7;
    char letter = 'A';
   
    void *ptr = &value;
    printf("value is: %d\n", *(int*)(ptr));

    ptr = &test;
    printf("value is: %f\n", *(double*)(ptr));

    ptr = &letter;
    printf("value is: %c\n", *(char*)(ptr));

    ptr = sum;
    printf("sum: %d\n", ((int (*)(int,int))ptr)(5,6));

    void *ptr1[] = {&value, &test, &letter , sum, array};

    printf("value: %d\n", *(int*)ptr1[0]);

    printf("value: %c\n", *((char*)ptr1[4]+1));

    return 0;
}

```
</details>
</details>

  <details>
  <summary><h3>Con trỏ hằng - Pointer to Constant.</h3></summary>

  - Khai báo:`const　<Kiểu dữ liệu>　* <Tên con trỏ>;`
- không thể thay đổi giá trị tại biến mà nó đang trỏ đến.
- Ứng dụng:Trong bài toán thao tác với mảng, lý do arr trả về địa chỉ ,là 1 con trỏ , có thể thay đổi giá trị thông qua địa chỉ .
- So sánh:

| Con trỏ thường | Con trỏ hằng|
|-------|-------|
| Có thể thay đổi giá trị | không thể thay đổi giá trị |

```C
 int *ptr;// con trỏ thường
 const int *ptr1;//con trỏ hằng
 x=5;
 ptr=&x;
 *ptr=10;
 printf("x la %d",x);//x =10
 *ptr1 =10;//lỗi , vì nó làm thay đổi giá trị biến
```

</details>

  <details>
  <summary><h3>Hằng Con trỏ - Constant Pointer</h3></summary>
- Khai báo:`int *const const_ptr = &value;`
- Đặc điểm:
	- Khi khai báo hằng con trỏ cần khởi tạo giá trị địa chỉ cho nó.
	- Khi hằng con trỏ đã trỏ đến 1 địa chỉ nào rồi,nó không thể trỏ tới bất kỳ 1 địa chỉ nào khác.
	- Có thể thay đổi được giá trị tại địa chỉ đã khởi gán ban đầu.

<details>
<summary>Ví dụ:</summary>

```C
#include <stdio.h>
#include <stdlib.h>
int main() {    
	int value = 5;    
	int test = 15;    
	int *const const_ptr = &value;   
	printf("value: %d\n", *const_ptr);    
	*const_ptr = 7   
	printf("value: %d\n", *const_ptr);   
	const_ptr = &test; // LỖI vì đã cố định vào value
	return 0;
}
```

</details>
</details>

  <details>
  <summary><h3>Mối quan hệ giữa mảng và con trỏ</h3></summary>
- Tên của mảng là một hằng con trỏ (địa chỉ không thay đổi được) 
- Giá trị của hằng con trỏ là địa chỉ của phần tử đầu tiên của mảng

**Vidu:**

        #include <stdio.h>
        int main(int argc, char const *argv[])
        {
            int a[5] = {1, 2, 3 , 4, 5 };

            printf("giá trị của a: %d\n", a); // a là hằng con trỏ
            printf("địa chỉ của phần tử a[0]: %d\n", &a[0]); // giá trị của hằng trỏ là địa chỉ của a[0]
            return 0;
        }
        
- Gán mảng cho một con trỏ thì có thể sử dụng con trỏ để thực hiện các thao tác giá trị, chỉ số của một mảng với điều kiện là trỏ một con trỏ tới địa chỉ đầu tiên của mảng a và sau đó có thể sử dụng như một cái mảng mặc dù nó là con trỏ

**Vidu:**

        #include <stdio.h>
        int main(int argc, char const *argv[])
        {
        int a[5] = {1, 2, 3 , 4, 5 };
        int *ptr = a;
        for(int i = 0; i < 5; i++){

        printf("gia tri cua mang: \n");
        printf("%d", ptr[i]);
            }
            return 0;

        }
- có thể sử dụng các toán tử ++ --... cho con trỏ khi đã gán mảng cho con trỏ.
> ++ptr;

</details>

  <details>
  <summary><h3>Con trỏ trỏ tới con trỏ</h3></summary>

- là một kiểu dữ liệu trong ngôn ngữ lập trình cho phép bạn lưu trữ địa chỉ của một con trỏ. 
- Con trỏ đến con trỏ cung cấp một cấp bậc trỏ mới, cho phép bạn thay đổi giá trị của con trỏ gốc. 
- Cấp bậc này có thể hữu ích trong nhiều tình huống, đặc biệt là khi bạn làm việc với các hàm cần thay đổi giá trị của con trỏ.

![pointer to pointer](./images/bai8_PointerToPointer.PNG)
<details>
<summary>Ví dụ:</summary>

```C
int test = 5;	//Address: 0x01
			 	//Value:	5
int *ptr = &test;//Address: 0x02
			 	//Value:	0x01
int **ptr1=&ptr;//Address: 0x03
			 	//Value:	0x01

#include <stdio.h>

int main() {
    int x = 10;
    int *ptr1 = &x;  // Con trỏ ptr1 trỏ đến biến x
    int **ptr2 = &ptr1;  // Con trỏ ptr2 trỏ đến con trỏ ptr1

    printf("Địa chỉ x: %p\n", &x);   //Địa chỉ x: 0x7ffe88cb3ab4
    printf("gia tri ptr1: %p\n", ptr1);//gia tri ptr1: 0x7ffe88cb3ab4
    printf("Địa chỉ con trỏ ptr1: %p\n", &ptr1);//Địa chỉ con trỏ ptr1: 0x7ffe88cb3ab8
    printf("Giá trị của ptr2 (địa chỉ của ptr1): %p\n", ptr2)//Giá trị của ptr2 (địa chỉ của ptr1): 0x7ffe88cb3ab8

    return 0;
}

```
</details>
</details>

  <details>
  <summary><h3>Con trỏ NULL</h3></summary>
- Khai báo:`int *ptr = NULL; `
- NULL pointer là một con trỏ không trỏ đến bất kỳ vùng nhớ cụ thể nào.
- Trong vđk khởi tạo con trỏ phải gán NULL
- Trước khi xài thì phải kiểm tra nó là NULL hay không.
- Lý do nếu kiểm tra không phải là NULL thì con trỏ đang trỏ tới 1 giá trị nào đó ,Tránh dereferencing (sử dụng giá trị mà con trỏ trỏ đến) làm sai chương trình.
- Khi xài xong 1 pointer thì phải gán nó bằng Null, để tránh sử dụng giá trị cũ của con trỏ.

<details>
<summary>Ví dụ:</summary>

```C

#include <stdio.h>
int main() {
    int *ptr = NULL;  // Gán giá trị NULL cho con trỏ 0x0000000

    if (ptr == NULL) {
        printf("Pointer is NULL\n");
    } else {
        printf("Pointer is not NULL\n");
    }

    int score_game = 5;
    if (ptr == NULL)
    {
        ptr = &score_game;
        *ptr = 30;
        ptr = NULL;
    }
}

```
</details>
</details>

</details>

  <details>
  <summary><h2>Linklist</h2></summary>
Tạo mảng nhân tạo có đặc trưng giống mảng truyền thống nhưng nó có thể chèn hoặc bớt ngẫu nhiên các phần tử vào mảng.

Nhược điểm: thời gian truy cập tuyến tính vì không phải là các ô nhớ liền kề nhau nên không thể truy cập ngẫu nhiên các ô nhớ bằng chỉ số mà phải duyệt từng giá trị một theo thứ tự.

- Phần tử cuối cùng trong DSLK trỏ vào NULL;
- Không lãng phí bộ nhớ nhưng cần thêm bộ nhớ để lưu phần con trỏ
- Các phần tử trong DSLK gọi là Node và được cấp phát động và được lưu ở bộ nhớ stack;
- Đây là CTDL cấp phát động nên khi còn bộ nhớ thì sẽ còn thêm được phần tử vào DSLK;

Gồm 2 phần: dữ liệu bài toán và một tham chiếu (hay liên kết) lưu địa chỉ tới các phần tử đứng sau kế tiếp

![Linklist](./images/bai10_linkList.PNG)


- Dùng trong các bài toán thao tác với mảng:Thêm, xóa, chèn ....phần tử vào mảng.
- Ngoài ra ta có các hàm thực hiện chức năng sau:

```C
node *createNode(int value); 
void push_back(node** array, int value); // thêm một node vào cuối
void push_front(node **array, int value); // them 1 node vao phia truoc
void pop_back(node **array); //  bỏ node cuối 
void pop_front(node **array); // xoa node dau tien
int front(node **array); // lay gia tri cua node dau tien
int back(node **array); // lay gia tri cua node cuoi cung
void insert(node **array, int value, int pos); // them 1 node vao mot vi tri bat ky
void deletee(node **array, int pos); // xoa 1 node tai mot vi tri bat ky
int size(node **array); // lay kich thuoc cua list
int get(node **array, int pos); 
bool empty(node **array); // kiem tra list co rong hay khong
```

  <details>
  <summary><h3>DSLK đơn</h3></summary>

#### a. Cấu trúc tự trỏ
            struct Node {
                uint8_t value; 
                struct Node *next;// link
            };
            typedef struct Node node;

- value: dữ liệu của node;
- node *next: con trỏ thuộc kiểu node tên next và lưu địa chỉ của phần tử đứng sau mang kiểu node.

Next của phần tử cuối cùng bao giờ cũng trỏ vào NULL.
#### b. Tạo một node mới: 

        node *createNode(uint8_t value){
            node *node2 = (node*) malloc(sizeof(node));
            node2->value = value;
        node2->next = NULL; // nốt mới tạo chưa liên kết với các node khác nên con trỏ trỏ tới NULL
            return node2;
        }

#### c. Thêm node vào đầu DSLK

##### hàm duyệt:

            void duyet (node *head){ 
                while(p->next != NULL){
                printf("%d", node -> value)
                    head = head->next;
                }
            }
            

- p = p -> next (p->next : địa chỉ của node kế tiếp): di chuyển từng node trong DSLK
- lấy địa chỉ của phần tử tiếp theo gán cho p khi đó p nhảy sang phần tử tiếp theo đến cuối khi p =  NULL thì vòng while dừng.

##### Thêm node vào đầu DSLK:

 
-  do hàm này làm thay đổi DSLK nên phải sử dụng truyền tham chiếu hoặc truyền con trỏ.

        void pushFront (**head, uint8_t value){
            node *newnode;
            newnode = createNode(value);
        //bước1: cho next của newnode trỏ vào node head hiện tại 
            newnode -> next = *head;  //*head là địa chỉ của node head
        //bước2: cập nhật node head bằng newnode
            *head = newnod;
        }

#### d.Thêm từng node vào DSLK

        void push_back(node **array, uint8_t value){ 
        node *temp, *p;
        temp = createNode(value);

        //kiểm tra giá trị của array bằng NULL thì tạo một node mới.
        if(*array = NULL){ 
            *array = temp;
        }
        else{ 

                //trong trường hợp ngược lại kiểm tra *array != NuLl thì gán địa chỉ con trỏ array cho p
            p = *array;
            
                // p trỏ đến next kiểm tra khác NULL, vì là chưa có node đầu tiền nên next sẽ == NUll nên không chạy vào vòng while

            while(p->next != NULL){
                p = p->next;
            }

                //khi con trỏ next == NUll thì sẽ tạo node mới khi đó node đầu tiên sẽ lưu địa chỉ node thứ 2 rôi chạy lại vào vòng while kiểm tra .
                
            p->next = temp;

        }
        }


<details>
<summary>Ví dụ</summary>

```C
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Định nghĩa cấu trúc của một node trong danh sách liên kết
typedef struct node
{
    int value;           // Giá trị của node
    struct node* next;   // Con trỏ trỏ đến node kế tiếp trong danh sách
} node;

// Hàm tạo một node mới với giá trị cho trước
node* createNode(int value)
{
    node* ptr = (node*)malloc(sizeof(node));  // Cấp phát bộ nhớ cho node mới
    ptr->value = value;                       // Gán giá trị
    ptr->next = NULL;                         // Khởi tạo con trỏ next là NULL
    return ptr;
}

// Hàm thêm một node vào cuối danh sách
void push_back(node** array, int value)
{
    node* temp = createNode(value);

    if (*array == NULL)
    {
        *array = temp;
    }
    else
    {
        node* p = *array;
        while (p->next != NULL)
        {
            p = p->next;
        }

        p->next = temp;
    }
}

// Hàm thêm một node vào đầu danh sách
void push_front(node** array, int value)
{
    node* temp = createNode(value);
    temp->next = *array;
    *array = temp;
}

// Hàm loại bỏ node cuối cùng trong danh sách
void pop_back(node** array)
{
    if (*array == NULL)
    {
        printf("Error: List is empty\n");
        return;
    }

    node* p = *array;

    if (p->next == NULL)
    {
        free(p);
        *array = NULL;
        return;
    }

    while (p->next->next != NULL)
    {
        p = p->next;
    }

    free(p->next);
    p->next = NULL;
}

// Hàm loại bỏ node đầu tiên trong danh sách
void pop_front(node** array)
{
    if (*array == NULL)
    {
        printf("Error: List is empty\n");
        return;
    }

    node* temp = *array;
    *array = (*array)->next;
    free(temp);
}

// Hàm trả về giá trị của node đầu tiên trong danh sách
int front(node** array)
{
    if (*array == NULL)
    {
        printf("Error: List is empty\n");
        return 0; // Return a default value or handle the error as needed
    }

    return (*array)->value;
}

// Hàm trả về giá trị của node cuối cùng trong danh sách
int back(node** array)
{
    if (*array == NULL)
    {
        printf("Error: List is empty\n");
        return 0; // Return a default value or handle the error as needed
    }

    node* p = *array;
    while (p->next != NULL)
    {
        p = p->next;
    }

    return p->value;
}

// Hàm chèn một node mới vào danh sách tại một vị trí cụ thể
void insert(node** array, int value, int pos)
{
    if (pos < 0)
    {
        printf("Error: Invalid position\n");
        return;
    }

    if (pos == 0)
    {
        push_front(array, value);
        return;
    }

    node* temp = createNode(value);
    node* p = *array;

    for (int i = 0; i < pos - 1 && p != NULL; i++)
    {
        p = p->next;
    }

    if (p == NULL)
    {
        printf("Error: Invalid position\n");
        free(temp);
        return;
    }

    temp->next = p->next;
    p->next = temp;
}

// Hàm xóa một node khỏi danh sách tại một vị trí cụ thể
void deletee(node** array, int pos)
{
    if (*array == NULL)
    {
        printf("Error: List is empty\n");
        return;
    }

    if (pos < 0)
    {
        printf("Error: Invalid position\n");
        return;
    }

    if (pos == 0)
    {
        pop_front(array);
        return;
    }

    node* p = *array;
    node* temp;

    for (int i = 0; i < pos - 1 && p != NULL; i++)
    {
        p = p->next;
    }

    if (p == NULL || p->next == NULL)
    {
        printf("Error: Invalid position\n");
        return;
    }

    temp = p->next;
    p->next = p->next->next;
    free(temp);
}

// Hàm trả về kích thước của danh sách
int size(node** array)
{
    int count = 0;
    node* p = *array;

    while (p != NULL)
    {
        count++;
        p = p->next;
    }

    return count;
}

// Hàm trả về giá trị của node tại một vị trí cụ thể trong danh sách
int get(node** array, int pos)
{
    int i = 0;
    node* p = *array;

    while (p != NULL && pos != i)
    {
        p = p->next;
        i++;
    }

    if (pos != i || p == NULL)
    {
        printf("Error: Invalid position\n");
        return 0; // Return a default value or handle the error as needed
    }

    return p->value;
}

// Hàm kiểm tra xem danh sách có rỗng hay không
bool empty(node** array)
{
    return (*array == NULL);
}

// Hàm main để kiểm tra các hàm đã triển khai
int main()
{
    node* arr = NULL;

    push_back(&arr, 2);
    push_back(&arr, 7);
    push_back(&arr, 4);
    push_back(&arr, 5);
    push_back(&arr, 3);
    push_back(&arr, 10);

    printf("Size: %d\n", size(&arr));

    push_front(&arr, 1);
    pop_back(&arr);

    printf("Front: %d\n", front(&arr));
    printf("Back: %d\n", back(&arr));

    insert(&arr, 99, 2);
    deletee(&arr, 4);

    for (int i = 0; i < size(&arr); i++)
    {
        printf("Value at position %d: %d\n", i, get(&arr, i));
    }

    printf("Is empty? %s\n", empty(&arr) ? "Yes" : "No");

    return 0;
}
```
</details>
</details>

  <details>
  <summary><h3>CẤP PHÁT ĐỘNG</h3></summary>

### 2.1.malloc

Dùng thư viện **stdlib.h** để dùng malloc.

Trong khi array là một mảng tĩnh không thể thay đổi kích thước được thì malloc là mảng động có thể thay đổi kích thước được.

Con trỏ lưu địa chỉ đầu tiên thì mảng lưu các địa chỉ liền kề

    >void malloc(sizeof(kiểu dữ liệu )* số lương ô nhớ cần cấp phát); 

- malloc sẽ trả về hàm void nên cần phải ép kiểu;

    >vidu: (uint8_t*)malloc(sizeof(uint8_t)*5); //lấy 5 bộ nhớ 1byte liền kề nhau kiểu uint8_t


### 2.2.realloc 

Dùng để mở rộng thêm bộ nhớ cấp phát động của mảng động (malloc)
    >ptr = void realloc(ptr, sizeof(kiểu dữ liệu) * kích thước tổng cấp phát)

vidu:  ptr = (uint8_t*)realloc(ptr, sizeof(uint8_t)*8 );
</details>
</details>


  <details>
  <summary><h2>Stack</h2></summary>

Ngăn xếp (STACK) là một danh sách tuyến tính, trong đó cho phép thêm và loại bỏ một phần tử khỏi ngăn xếp luôn luôn thực hiện ở một đầu gọi là đỉnh (top).

![Linklist](./images/bai11_stack.PNG)

**Các Phép Toán Cơ Bản trên Ngăn Xếp**

- push(): Chèn một phần tử vào ngăn xếp.
- pop(): Loại bỏ một phần tử khỏi ngăn xếp.
- peek(): Lấy giá trị của phần tử ở đỉnh mà không loại bỏ nó.
- isempty(): Kiểm tra xem ngăn xếp có trống không.
- isfull(): Kiểm tra xem ngăn xếp có đầy không.
- size(): Trả về kích thước của ngăn xếp.

 

**Các phép toán hoạt động như sau:**
- Sử dụng một con trỏ được gọi là TOP để theo dõi phần tử đỉnh trong ngăn xếp.
- Khi khởi tạo ngăn xếp, ta đặt giá trị của nó là -1 để kiểm tra xem ngăn xếp có trống không bằng cách so sánh TOP == -1.
- Khi đẩy một phần tử, ta tăng giá trị của TOP và đặt phần tử mới vào vị trí mà TOP đang chỉ đến.
- Khi lấy ra một phần tử, ta trả về phần tử mà TOP đang chỉ đến và giảm giá trị của nó.
- Trước khi đẩy, ta kiểm tra xem ngăn xếp đã đầy chưa.
- Trước khi lấy ra, ta kiểm tra xem ngăn xếp đã trống không chưa.

    ![Linklist](./images/stack.PNG)

### 1.1.Hàm kiểm tra ngăn xếp đầy

// return true if stack empty else false

            bool isEmpty(){
            if(i == -1){
                return true;
            }
            else{
                return false;
            }
        }
### 1.2.Hàm kiểm tra ngăn xếp rỗng
 // return true if stack is full else false

            bool isFull(){
                if(i == SIZE - 1){
                    return true;
                }
                else{
                    return false;
                }
            }

### 1.3.Hàm thêm một khối vào ngăn xếp
// to insert an elememt into the stack

            void push(uint8_t stack[], uint8_t value){
                if(isFull() == true){
                    printf("stack is full\n");
                }
                else{
                    ++i;
                    stack[i] = value;
                }
            }
### 1.4.Hàm xóa một khối khỏi ngăn xếp
// to remove an element from the stack

        void pop(uint8_t stack[]){
            if(isEmpty() == true){
                printf("stack is empty\n");
            }
            else {
                stack[i--] =='\0';
            }
        }
### 1.6.Hàm trả về một khối cảu ngăn xếp     
// return the top element of the stack

        uint8_t top (const uint8_t stack[]){
            return stack[i];
        }
### 1.7.Hàm trả về kích thước của ngăn xếp       
// return the size of the stack

        uint8_t size(){
            return i + 1;
        }
 
 <details>
<summary>Ví dụ1:</summary>

```C
	#include <stdio.h>
	#include <stdlib.h>
	
	typedef struct Stack {
	    int* items; // mảng để lưu giá trị của từng ô
	    int size;
	    int top;
	} Stack;
	
	void initialize( Stack *stack, int size) {
	    stack->items = (int*) malloc(sizeof(int) * size);
	    stack->size = size;
	    stack->top = -1;
	}
	
	int is_empty( Stack stack) {
	    return stack.top == -1;
	}
	
	int is_full( Stack stack) {
	    return stack.top == stack.size - 1;
	}
	
	void push( Stack *stack, int value) {
	    if (!is_full(*stack)) {
	        stack->items[++stack->top] = value;
	    } else {
	        printf("Stack overflow\n");
	    }
	}
	
	int pop( Stack *stack) {
	    if (!is_empty(*stack)) {
	        return stack->items[stack->top--];
	    } else {
	        printf("Stack underflow\n");
	        return -1;
	    }
	}
	
	int top( Stack stack) {
	    if (!is_empty(stack)) {
	        return stack.items[stack.top];
	    } else {
	        printf("Stack is empty\n");
	        return -1;
	    }
	}
	
	int main() {
	    Stack stack1;
	    initialize(&stack1, 5);
	
	
	    push(&stack1, 10);
	    push(&stack1, 20);
	    push(&stack1, 30);
	    push(&stack1, 40);
	    push(&stack1, 50);
	    push(&stack1, 60);
	
	    printf("Top element: %d\n", top(stack1)); // 50
	
	    printf("Pop element: %d\n", pop(&stack1)); // 50
	    printf("Pop element: %d\n", pop(&stack1)); // 40
	
	    printf("Top element: %d\n", top(stack1)); // 30
	
	    return 0;
	}

```
</details>

 <details>
<summary>Ví dụ 2:</summary>

```c
	#include <stdio.h>
	#include <stdlib.h>

	void push();
	void pop();
	void display();

	struct node {
	    int data;
	    struct node* next;
	};
	
	struct node* temp; // Variable to store the top of the stack
	
	int main() {
	    printf("LINKED LIST IMPLEMENTATION USING STACKS\n\n");
	    do {
	        printf("1. Insert\n2. Delete\n3. Display\n4. Exit\n\n");
	        printf("Enter your choice:");
	        int choice; scanf("%d", &choice);
	        
	        switch (choice) {
	            case 1:
	                push();
	                break;
	            case 2:
	                pop();
	                break;
	            case 3:
	                display();
	                break;
	            case 4:
	                exit(0);
	                break;
	            default:
	                printf("Please re-enter!\n");
	                break;
	        }
	    } while (choice != 4);
	    return 0;
	}
	
	void push() {
	    int data;
	    struct node* pointer = (struct node*)malloc(sizeof(struct node));
	    
	    if (pointer == NULL) printf("Stack overflow\n");
	    else {
	        printf("Enter the element to be inserted: ");
	        scanf("%d", &data);
	        
	        if (temp == NULL) {
	            pointer->data = data;
	            pointer->next = NULL;
	            temp = pointer;
	        } else {
	            pointer->data = data;
	            pointer->next = temp;
	            temp = pointer;
	        }
	    }
	}
	
	void pop() {
	    int item;
	    struct node* pointer;
	    
	    if (temp == NULL) {
	        printf("Stack underflow\n");
	    }
	    else {
	        item = temp->data;
	        pointer = temp;
	        temp = temp->next;
	        free(pointer);
	        printf("The deleted item is %d\n", item);
	    }
	}
	
	void display() {
	    struct node* pointer;
	    pointer = temp;
	    
	    if (pointer == NULL) {
	        printf("Stack underflow\n");
	    }
	    else {
	        printf("The elements of the stack are:\n");
	        
	        while (pointer != NULL) {
	            printf("%d\n", pointer->data);
	            pointer = pointer->next;
	        }
	    }
	}

```
</details>       
</details>

  <details>
  <summary><h2>Queue</h2></summary>

Hàng đợi là một danh sách tuyến tính trong đó, phép bổ sung một phần tử vào hàng đợi được thực hiện ở một đầu, gọi là cuối hàng(rear) và phép loại bỏ một phần tử được thực hiện ở đầu kia, gọi là đầu hàng(front).

Cơ cấu của hàng đợi là vào ở một đầu, ra ở một đầu, phần tử vào trước thì ra trước, phầm tử vào sau thì ra sau.

Hàng đợi còn được gọi là danh sách kiểu FIFO(First In First Out)

![Linklist](./images/bai12_queue.PNG)

**Các Phép Toán Cơ Bản trên Hàng Đợi**

- Enqueue: Thêm một phần tử vào cuối hàng đợi.
- Dequeue: Loại bỏ một phần tử từ đầu hàng đợi.
- IsEmpty: Kiểm tra xem hàng đợi có trống không.
- IsFull: Kiểm tra xem hàng đợi có đầy không.
- Peek: Lấy giá trị ở đầu hàng đợi mà không loại bỏ nó.

**Các phép toán trên hàng đợi hoạt động như sau:**

  + Hai con trỏ FRONT và REAR
  + FRONT theo dõi phần tử đầu tiên của hàng đợi
  + REAR theo dõi phần tử cuối cùng của hàng đợi
  + Ban đầu, đặt giá trị của FRONT và REAR là -1
- quy ước: 

        rear = -1
        front = -1

- biến thể của queue: 
    + có hai trường hợp queue rỗng: front = rear = -1(khi chưa gán data), rear = front(khi lấy hết data)

  ![Linklist](./images/queue1.PNG)
   ![Linklist](./images/queue2.PNG)

   <details>
<summary>Ví dụ:</summary>

```C
	#include <stdio.h>
	#include <stdlib.h>
	
	
	typedef struct Queue {
	    int* items; // mảng để lưu giá trị của từng ô
	    int size;
	    int front, rear; // để xác định phần tử nào đứng đầu, phần tử nào đứng cuối hàng
	} Queue;
	
	void initialize(Queue *queue, int size) {
	    queue->items = (int*) malloc(sizeof(int)* size);
	    queue->front = -1;
	    queue->rear = -1;
	    queue->size = size;
	}
	
	int is_empty(Queue queue) {
	    return queue.front == -1;
	}
	
	int is_full(Queue queue) {
	    return (queue.rear + 1) % queue.size == queue.front;
	}
	
	void enqueue(Queue *queue, int value) {
	    if (!is_full(*queue)) {
	        if (is_empty(*queue)) {
	            queue->front = queue->rear = 0;
	        } else {
	            queue->rear = (queue->rear + 1) % queue->size;
	        }
	        queue->items[queue->rear] = value;
	    } else {
	        printf("Queue overflow\n");
	    }
	}
	
	int dequeue(Queue *queue) {
	    if (!is_empty(*queue)) {
	        int dequeued_value = queue->items[queue->front];
	        if (queue->front == queue->rear) {
	            queue->front = queue->rear = -1;
	        } else {
	            queue->front = (queue->front + 1) % queue->size;
	        }
	        return dequeued_value;
	    } else {
	        printf("Queue underflow\n");
	        return -1;
	    }
	}
	
	int front(Queue queue) {
	    if (!is_empty(queue)) {
	        return queue.items[queue.front];
	    } else {
	        printf("Queue is empty\n");
	        return -1;
	    }
	}
	
	int main() {
	    Queue queue;
	    initialize(&queue, 3);
	
	    enqueue(&queue, 10);
	    enqueue(&queue, 20);
	    enqueue(&queue, 30);
	
	    printf("Front element: %d\n", front(queue));
	
	    printf("Dequeue element: %d\n", dequeue(&queue));
	    printf("Dequeue element: %d\n", dequeue(&queue));
	
	    printf("Front element: %d\n", front(queue));
	
	    enqueue(&queue, 40);
	    enqueue(&queue, 50);
	    printf("Dequeue element: %d\n", dequeue(&queue));
	    printf("Front element: %d\n", front(queue));
	
	    return 0;
	}

```
</details>


<details>
  <summary><h2>Binary Search</h2></summary>

- Tìm kiếm nhị phân (Binary Search) là một thuật toán tìm kiếm trên m mảng đã được sắp xếp. Ý tưởng  là so sánh giá trị cần tìm với giá trị ở giữa của mảng, và dựa vào kết quả của so sánh để xác định xem giá trị cần tìm có thể nằm ở nửa trên hay nửa dưới của mảng

<details>
<summary>Ví dụ:</summary>

```C
#include <stdio.h>

int binarySearch(int arr[], int low, int high, int target) {
    while (low <= high) {
        int mid = low + (high - low) / 2;

        // Kiểm tra xem giá trị ở giữa có bằng giá trị cần tìm không
        if (arr[mid] == target)
            return mid;

        // Nếu giá trị ở giữa lớn hơn target, tìm ở nửa trái của mảng
        if (arr[mid] > target)
            high = mid - 1;

        // Nếu giá trị ở giữa nhỏ hơn target, tìm ở nửa phải của mảng
        else
            low = mid + 1;
    }

    // Trả về -1 nếu không tìm thấy giá trị cần tìm
    return -1;
}

int main() {
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 45, 50};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target;
    printf("nhap gia tri can tim\n");
    scanf("%d",&target);

    int result = binarySearch(arr, 0, n - 1, target);

    if (result != -1)
        printf("Giá trị %d được tìm thấy tại vị trí %d.\n", target, result);
    else
        printf("Giá trị %d không tồn tại trong mảng.\n", target);

    return 0;
}

```
</details>
</details>

<details>
  <summary><h2>Bitmask </h2></summary>

**Khái niệm**:
- Bitmask là một kỹ thuật dùng để kiểm tra, đặt, hoặc xóa bit cụ thể hoặc (flags)
- khi muốn Set 1 bit tại ví trí chỉ cần dịch bit 1 tới vị trí Cần SET và OR với iá trị hiện tại
- Khi muốn Clear bit tai vị tri chỉ cần dịch bit 1 tới vị trí cần Clear , đảo ngược hết bit đó  và AND với giá trị hiện tại
- Ví dụ:

```C
	uint8_t x = 0;/0X0000 0000
	// Muốn set tại vị tri 1 
	x = x | (1 << 1);//0x0000 0010
	x = x & ~(1 << 1);0x0000 0000
	1<<1:dịch bit 1 tới vị trí số 1:0000 0010
	1<<2:dịch bit 1 tới vị trí số 2:0000 0100


```
<details>
<summary>Ví dụ 1 </summary>

```C

#include <stdio.h>
#include <stdint.h>


#define GENDER        1 << 0  // Bit 0: Giới tính (0 = Nữ, 1 = Nam)
#define TSHIRT        1 << 1  // Bit 1: Áo thun (0 = Không, 1 = Có)
#define HAT           1 << 2  // Bit 2: Nón (0 = Không, 1 = Có)
#define SHOES         1 << 3  // Bit 3: Giày (0 = Không, 1 = Có)
// Tự thêm 5 tính năng khác
#define FEATURE1      1 << 4  // Bit 4: Tính năng 1
#define FEATURE2      1 << 5  // Bit 5: Tính năng 2
#define FEATURE3      1 << 6  // Bit 6: Tính năng 3
#define FEATURE4      1 << 7  // Bit 7: Tính năng 4

void enableFeature(uint8_t *features, uint8_t feature) {
    *features |= feature;
}

void disableFeature(uint8_t *features, uint8_t feature) {
    *features &= ~feature;
}


int isFeatureEnabled(uint8_t features, uint8_t feature) {
    return (features & feature) != 0;
}

void listSelectedFeatures(uint8_t features) {
    printf("Selected Features:\n");

    if (features & GENDER) {
        printf("- Gender\n");
    }
    if (features & TSHIRT) {
        printf("- T-Shirt\n");
    }
    if (features & HAT) {
        printf("- Hat\n");
    }
    if (features & SHOES) {
        printf("- Shoes\n");
    }
    // Thêm các điều kiện kiểm tra cho các tính năng khác
}

void removeFeatures(uint8_t *features, uint8_t unwantedFeatures) {
    *features &= ~unwantedFeatures;
}


int main() {
    uint8_t options = 0;

    // Thêm tính năng 
    enableFeature(&options, GENDER | TSHIRT | HAT);

    removeFeatures(&options, TSHIRT);

    // Liệt kê các tính năng đã chọn
    listSelectedFeatures(options);
    
    return 0;
}

```

</details>

<details>
<summary>Ví dụ 2 </summary>

```	C
#include <stdio.h>

#define LED1 1 << 0 // 0001
#define LED2 1 << 1 // 0010
#define LED3 1 << 2 // 0100
#define LED4 1 << 3 // 1000


void enableLED(unsigned int *GPIO_PORT, unsigned int LED) {
    *GPIO_PORT |= LED;
}

void disableLED(unsigned int *GPIO_PORT, unsigned int LED) {
    *GPIO_PORT &= ~LED;
}


int main() {
    unsigned int GPIO_PORT = 0; // Giả sử là biến điều khiển cổng GPIO

    // Bật LED1 và LED3
    enableLED(&GPIO_PORT, LED1 | LED3);
    if (GPIO_PORT & LED1 )
    {
        printf("LED1 is on\n");
    }

    if (GPIO_PORT & LED2)
    {
        printf("LED2 is on\n");
    }

    if (GPIO_PORT & LED3)
    {
        printf("LED3 is on\n");
    }
    
    // Tắt LED1 và bật LED2
    disableLED(&GPIO_PORT, LED1);
    enableLED(&GPIO_PORT, LED2);

    if (GPIO_PORT & LED1 )
    {
        printf("LED1 is on\n");
    }

    if (GPIO_PORT & LED2)
    {
        printf("LED2 is on\n");
    }

    if (GPIO_PORT & LED3)
    {
        printf("LED3 is on\n");
    }

    // Cập nhật trạng thái của GPIO_PORT tương ứng với hardware

    return 0;
}
```
</details>
</details>

<details>
  <summary><h2> JSON</h2></summary>

> https://www.w3schools.com/js/js_json_intro.asp
>
> https://www.geeksforgeeks.org/cjson-json-file-write-read-modify-in-c/

- JSON là viết tắt của "JavaScript Object Notation" (Định dạng đối tượng JavaScript).
- JSON là một định dạng văn bản được sử dụng để lưu trữ và truyền dữ liệu; nó được sử dụng để trao đổi dữ liệu giữa các ứng dụng và dịch vụ web.
- JSON là "tự mô tả", dễ đọc và viết cho cả con người và máy tính.

**Trong JSON, giá trị phải thuộc một trong các loại dữ liệu sau:**

- Một chuỗi (phải được viết trong dấu ngoặc kép) -> Ví dụ: {"name":"John"}
- Một số (phải là số nguyên hoặc số thực) -> Ví dụ: {"age":30}
- Một đối tượng (Các giá trị trong JSON có thể là đối tượng) -> Ví dụ: { "employee":{"name":"John", "age":30, "city":"New York"} }
- Một mảng -> Ví dụ: { "employees":["John", "Anna", "Peter"] }
- Một giá trị boolean -> Ví dụ: {"sale":true}
null -> Ví dụ: {"middlename":null}
- Giá trị JSON không thể là một trong các loại dữ liệu sau:
Một hàm,Một ngày,undefined.

```C
	{ "name": "Bob Johnson", "age": 35, "city": "Chicago" },
	{ "name": "John Doe", "age": 30, "city": "New York", "occupation": "Software Engineer", "isStudent": false },
	{
	    "name": "Jane Smith",
	    "age": null,
	    "city": "Los Angeles",
	    "contact": { "email": "jane.smith@example.com", "phone": "555-1234" }
	}

```

<details>
<summary>Ví dụ:</summary>

```C
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include <stddef.h>
	#include <ctype.h>
	#include <stdbool.h>
	
	typedef enum {
	    JSON_NULL,
	    JSON_BOOLEAN,
	    JSON_NUMBER,
	    JSON_STRING,
	    JSON_ARRAY,
	    JSON_OBJECT
	} JsonType;
	
	typedef struct JsonValue {
	    JsonType type;
	    union {
	        int boolean; double number; char *string;
	        struct {
	            struct JsonValue *values;
	            size_t count; // số lượng element
	        } array;
	        struct {
	            char **keys;
	            struct JsonValue *values;
	            size_t count; // số cặp key-value
	        } object;
	    } value;
	} JsonValue;
	
	JsonValue *parse_json(const char **json);
	
	void free_json_value(JsonValue *json_value);
	
	static void skip_whitespace(const char **json) {
	    while (isspace(**json)) {
	        (*json)++;
	    }
	}
	
	JsonValue *parse_null(const char **json) {
	    skip_whitespace(json);
	    if (strncmp(*json, "null", 4) == 0) { // khi bắt gặp đc chữ n -> nó lấy thêm 3 phần tử tiếp theo -> so sánh với null
	        JsonValue *value = (JsonValue *) malloc(sizeof(JsonValue));
	        value->type = JSON_NULL; 
	        *json += 4;
	        return value;
	    }
	    return NULL;
	}
	
	JsonValue *parse_boolean(const char **json) {
	    skip_whitespace(json);
	    JsonValue *value = (JsonValue *) malloc(sizeof(JsonValue));
	    if (strncmp(*json, "true", 4) == 0) {
	        value->type = JSON_BOOLEAN;
	        value->value.boolean = true;
	        *json += 4;
	    } else if (strncmp(*json, "false", 5) == 0) {
	        value->type = JSON_BOOLEAN;
	        value->value.boolean = false;
	        *json += 5;
	    } else {
	        free(value);
	        return NULL;
	    }
	    return value;
	}
	
	JsonValue *parse_number(const char **json) {
	    skip_whitespace(json);
	    char *end; //:') 
	
	    double num = strtod(*json, &end);
	    if (end != *json) {
	        JsonValue *value = (JsonValue *) malloc(sizeof(JsonValue));
	        value->type = JSON_NUMBER;
	        value->value.number = num;
	        *json = end;
	        return value;
	    }
	    return NULL;
	}
	
	JsonValue *parse_string(const char **json) {
	    skip_whitespace(json);
	
	    if (**json == '\"') {
	        (*json)++;
	        const char *start = *json;
	        while (**json != '\"' && **json != '\0') {
	            (*json)++;
	        }
	        if (**json == '\"') {
	            size_t length = *json - start; // 3
	            char *str = (char *) malloc((length + 1) * sizeof(char));
	            strncpy(str, start, length);
	            str[length] = '\0';
	
	            JsonValue *value = (JsonValue *) malloc(sizeof(JsonValue));
	            value->type = JSON_STRING;
	            value->value.string = str;
	            (*json)++;
	            return value;
	        }
	    }
	    return NULL;
	}
	
	JsonValue *parse_array(const char **json) {
	    skip_whitespace(json);
	    if (**json == '[') {
	        (*json)++;
	        skip_whitespace(json);
	
	        JsonValue *array_value = (JsonValue *)malloc(sizeof(JsonValue));
	        array_value->type = JSON_ARRAY;
	        array_value->value.array.count = 0;
	        array_value->value.array.values = NULL;
	
	        /*
	        double arr[2] = {};
	        arr[0] = 30;
	        arr[1] = 70;
	        */
	
	        while (**json != ']' && **json != '\0') {
	            JsonValue *element = parse_json(json); // 70
	            if (element) {
	                array_value->value.array.count++;
	                array_value->value.array.values = (JsonValue *)realloc(array_value->value.array.values, array_value->value.array.count * sizeof(JsonValue));
	                array_value->value.array.values[array_value->value.array.count - 1] = *element;
	                free(element);
	            } else {
	                break;
	            }
	            skip_whitespace(json);
	            if (**json == ',') {
	                (*json)++;
	            }
	        }
	        if (**json == ']') {
	            (*json)++;
	            return array_value;
	        } else {
	            free_json_value(array_value);
	            return NULL;
	        }
	    }
	    return NULL;
	}
	
	JsonValue *parse_object(const char **json) {
	    skip_whitespace(json);
	    if (**json == '{') {
	        (*json)++;
	        skip_whitespace(json);
	
	        JsonValue *object_value = (JsonValue *)malloc(sizeof(JsonValue));
	        object_value->type = JSON_OBJECT;
	        object_value->value.object.count = 0;
	        object_value->value.object.keys = NULL;
	        object_value->value.object.values = NULL;
	
	        while (**json != '}' && **json != '\0') {
	            JsonValue *key = parse_string(json);
	            if (key) {
	                skip_whitespace(json);
	                if (**json == ':') {
	                    (*json)++;
	                    JsonValue *value = parse_json(json);
	                    if (value) {
	                        object_value->value.object.count++;
	                        object_value->value.object.keys = (char **)realloc(object_value->value.object.keys, object_value->value.object.count * sizeof(char *));
	                        object_value->value.object.keys[object_value->value.object.count - 1] = key->value.string;
	
	                        object_value->value.object.values = (JsonValue *)realloc(object_value->value.object.values, object_value->value.object.count * sizeof(JsonValue));
	                        object_value->value.object.values[object_value->value.object.count - 1] = *value;
	                        free(value);
	                    } else {
	                        free_json_value(key);
	                        break;
	                    }
	                } else {
	                    free_json_value(key);
	                    break;
	                }
	            } else {
	                break;
	            }
	            skip_whitespace(json);
	            if (**json == ',') {
	                (*json)++;
	            }
	        }
	        if (**json == '}') {
	            (*json)++;
	            return object_value;
	        } else {
	            free_json_value(object_value);
	            return NULL;
	        }
	    }
	    return NULL;
	}
	
	JsonValue *parse_json(const char **json) { // làm việc với giá trị json_str_value 
	    while (isspace(**json)) {
	        (*json)++;
	    }
	
	    switch (**json) {
	        case 'n':
	            return parse_null(json);
	        case 't':
	        case 'f':
	            return parse_boolean(json);
	        case '\"':
	            return parse_string(json);
	        case '[':
	            return parse_array(json);
	        case '{':
	            return parse_object(json);
	        default:
	            if (isdigit(**json) || **json == '-') return parse_number(json);
	            else return NULL; // Lỗi phân tích cú pháp
	    }
	}
	
	void free_json_value(JsonValue *json_value) {
	    if (json_value == NULL) return;
	    
	    switch (json_value->type) {
	        case JSON_STRING:
	            free(json_value->value.string);
	            break;
	        case JSON_ARRAY:
	            for (size_t i = 0; i < json_value->value.array.count; i++) {
	                free_json_value(&json_value->value.array.values[i]);
	            }
	            free(json_value->value.array.values);
	            break;
	        case JSON_OBJECT:
	            for (size_t i = 0; i < json_value->value.object.count; i++) {
	                free(json_value->value.object.keys[i]);
	                free_json_value(&json_value->value.object.values[i]);
	            }
	            free(json_value->value.object.keys);
	            free(json_value->value.object.values);
	            break;
	        default:
	            break;
	    }
	}
	
	void test(JsonValue* json_value){
	    if (json_value != NULL && json_value->type == JSON_OBJECT) {
	        // Truy cập giá trị của các trường trong đối tượng JSON
	        size_t num_fields = json_value->value.object.count;
	        size_t num_fields2 = json_value->value.object.values->value.object.count;
	        for (size_t i = 0; i < num_fields; ++i) {
	
	            char* key = json_value->value.object.keys[i];
	            JsonValue* value = &json_value->value.object.values[i];
	
	            JsonType type = (int)(json_value->value.object.values[i].type);
	
	            if(type == JSON_STRING) printf("%s: %s\n", key, value->value.string);
	        
	            if(type == JSON_NUMBER) printf("%s: %f\n", key, value->value.number);
	        
	            if(type == JSON_BOOLEAN) printf("%s: %s\n", key, value->value.boolean ? "True":"False");
	
	            if(type == JSON_OBJECT){
	                printf("%s: \n", key);
	                test(value);
	            }
	
	            if(type == JSON_ARRAY){
	                printf("%s: ", key);
	                for (int i = 0; i < value->value.array.count; i++) {
	                   test(value->value.array.values + i);
	                } 
	                printf("\n");
	            }
	        }
	    } else {
		    if(json_value->type == JSON_STRING) printf("%s ", json_value->value.string);
		    
		    if(json_value->type == JSON_NUMBER) printf("%f ", json_value->value.number);
		
		    if(json_value->type == JSON_BOOLEAN) printf("%s ", json_value->value.boolean ? "True":"False");
		
		    if(json_value->type == JSON_OBJECT){
			printf("%s: \n", json_value->value.object.keys);
			test(json_value->value.object.values);          
	            }
	      }
	}
	
	int main(int argc, char const *argv[]) {
	     
	     // Chuỗi JSON đầu vào
	    const char* json_str = "{"
	                        "\"1001\":{"
	                          "\"SoPhong\":3,"
	                          "\"NguoiThue\":{"
	                            "\"Ten\":\"Nguyen Van A\","
	                            "\"CCCD\":\"1920517781\","
	                            "\"Tuoi\":26,"
	                            "\"ThuongTru\":{"
	                              "\"Duong\":\"73 Ba Huyen Thanh Quan\","
	                              "\"Phuong_Xa\":\"Phuong 6\","
	                              "\"Tinh_TP\":\"Ho Chi Minh\""
	                            "}"
	                          "},"
	                          "\"SoNguoiO\":{"
	                            "\"1\":\"Nguyen Van A\","
	                            "\"2\":\"Nguyen Van B\","
	                            "\"3\":\"Nguyen Van C\""
	                          "},"
	                          "\"TienDien\": [24, 56, 98],"
	                          "\"TienNuoc\":30.000"
	                        "},"
	                        "\"1002\":{"
	                          "\"SoPhong\":5,"
	                          "\"NguoiThue\":{"
	                            "\"Ten\":\"Phan Hoang Trung\","
	                            "\"CCCD\":\"012345678912\","
	                            "\"Tuoi\":24,"
	                            "\"ThuongTru\":{"
	                              "\"Duong\":\"53 Le Dai Hanh\","
	                              "\"Phuong_Xa\":\"Phuong 11\","
	                              "\"Tinh_TP\":\"Ho Chi Minh\""
	                            "}"
	                          "},"
	                          "\"SoNguoiO\":{"
	                            "\"1\":\"Phan Van Nhat\","
	                            "\"2\":\"Phan Van Nhi\","
	                            "\"2\":\"Phan Van Tam\","
	                            "\"3\":\"Phan Van Tu\""
	                          "},"
	                          "\"TienDien\":23.000,"
	                          "\"TienNuoc\":40.000"
	                        "}"
	                      "}";
	    
	
	    // Phân tích cú pháp chuỗi JSON
	    JsonValue* json_value = parse_json(&json_str);
	
	   test(json_value);
	
	    // Kiểm tra kết quả phân tích cú pháp
	
	       // Giải phóng bộ nhớ được cấp phát cho JsonValue
	    free_json_value(json_value);
	    
	        //printf("test = %x", '\"');
	
	       // hienthi(5);
	    
	    return 0;
	}






```
</details>
</details>

<details>
  <summary><h2> File operations </h2></summary>

**Những thứ liên quan đến file.csv**
- File CSV (Comma-Separated Values) là một loại file văn bản  để lưu trữ  dữ liệu dưới dạng bảng.
- Ví dụ 1 file example.csv có nội dung

	+ UID	Room	Name
	+	1	A 101	John Doe
	+	2	B202	Jane Smith
	+	3	C303	Bob Johnson4

- Các hàm để thao tác file:
	+ fprintf():Ghi chuỗi vào File, và có thể thêm danh sách các đối số 
	+ fputs() :Ghi chuỗi vào File
	+ fputc() :Ghi một ký tự vào File
	+ fwrite() :Ghi một số byte được chỉ định vào File .bin
	+ fclose(): Đóng File đã mở
	+ feof(): Để kiểm tra địa chỉ hiện tại có phải ký tự cuối cùng của File hay chưa

- Ví dụ thêm dữ liệu vào file example.csv.		

```c
#include <stdio.h>
void addRow(const char* filename, const char* uid, const char* room, const char* name) {
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        printf("Không thể mở file %s để ghi dữ liệu.\n", filename);
        return;
    }
    fprintf(file, "%s,%s,%s\n", uid, room, name);

    fclose(file);
}
int main() {
    addRow("example.csv", "4", "D404", "A Johson");
    addRow("example.csv", "5", "D424", "Ale ");
    addRow("example.csv", "6", "D425", "Alice ");
    return 0;
}
```
</details>

</details>
  <details>
  <summary><h1>C++</h1></summary>

<details>
  <summary><h2>Class</h2></summary>
	
### Class là gì?
- Class là một cấu trúc dữ liệu , nó bao gồm thuộc tính và hành vi của đối tượng
- Object là 1 đối tượng có thuộc tính và hành vi được tạo ra từ class
- Biến trong class gọi là `PROPERTY`.
- Hàm trong class gọi là `METHOD`.
- Ví dụ:

```C++
class ClassName {
private:   
// Các thành phần riêng tư (private) chỉ có thể truy cập bên trong lớp   
// Dữ liệu thành viên, hàm thành viên, ...
protected:    
// Các thành phần bảo vệ (protected) tương tự như private, nhưng có thể truy cập từ lớp kế thừa
public:
    // Các thành phần công khai (public) được truy cập từ bên ngoài lớp
	// Dữ liệu thành viên, hàm thành viên, ...
	// Hàm thành viên và các phương thức khác có thể được định nghĩa tại đây
	// ..
};

```
**Constructor**
-  Constructor  là một method , nó sẽ tự động gọi khi khởi tạo object. Constructor sẽ có tên trùng với tên của class,Nó dùng để khởi tạo giá trị cho đối tượng 
-  Có hai loại chính:
	+ Default Constructor (Constructor mặc định):Hệ thống sẽ tự động tạo
	+ Parameterized Constructor (Constructor với tham số):   constructor được khởi tạo và có tham số truyền vào.
	+  Có constructor là cần thiết và quan trọng:
		+ Khởi tạo đối tượng
		+ Thiết lập các giá trị ban đầu
<details>
<summary>Ví dụ:</summary>

```C++
#include <iostream>

class HinhChuNhat {
public:
    double chieuDai;
    double chieuRong;

    // Parameterized Constructor
    HinhChuNhat(int dai = 5, int rong = 3) {
        chieuDai = dai;
        chieuRong = rong;
    }

    // Hàm tính diện tích
    double tinhDienTich() {
        return chieuDai * chieuRong;
    }
};

int main() {
    // Tạo đối tượng HinhChuNhat và sử dụng constructor với giá trị mặc định
    HinhChuNhat hinhCN1;

    // Tạo đối tượng HinhChuNhat và truyền giá trị khác cho constructor
    HinhChuNhat hinhCN2(7, 4);

    // Hiển thị diện tích của hình chữ nhật 1 và 2
    std::cout << "Dien tich hinh chieuDai1: " << hinhCN1.tinhDienTich() << std::endl;
    std::cout << "Dien tich hinh chieuDai2: " << hinhCN2.tinhDienTich() << std::endl;

    return 0;
}


```
</details>

**copy Constructor**
- Mục đích của constructor sao chép là sao chép các giá trị thuộc tính từ một đối tượng đã tồn tại sang một đối tượng mới
- Trong C++ có hai loại copy được tạo bởi hàm xây dựng đó là:
	+ Shallow copy
		+ Hàm xây dựng sao chép mặc định chỉ có thể tạo shallow copy.
		+ hỉ các giá trị của các property được sao chép từ đối tượng gốc sang đối tượng mới.
		+ Nếu các property là các con trỏ , sẽ chỉ sao chép địa chỉ của các con trỏ đó dẫn đến nếu 1 đối tượng bị thay đổi sẽ ảnh hưởng tới đối tượng khác

	+ Deep copp
		+ Deep copy tự động cấp phát bộ nhớ cho bản sao và sau đó sao chép giá trị thực cho bản sao
		+ Điều này đảm bảo rằng các đối tượng không chia sẻ cùng một vùng nhớ.thay đổi dữ liệu trong một đối tượng không ảnh hưởng đến dữ liệu của đối tượng khác.

<details>
<summary>Ví dụ:</summary>

```c++
#include <iostream>

using namespace std;

class TestShallowCopy {
    int a;
    int b;
    int *p;

public:
    TestShallowCopy() {
        p = new int;
    }

    TestShallowCopy(const TestShallowCopy &t) {
        a = t.a;
        b = t.b;
        p = new int; // Cấp phát vùng nhớ mới
        *p = *(t.p); // Sao chép giá trị của *p từ đối tượng gốc sang đối tượng mới
    }

    ~TestShallowCopy() {
        delete p; // Giải phóng bộ nhớ khi đối tượng bị hủy
    }

    void TaoDuLieu(int x, int y, int z) {
        a = x;
        b = y;
        *p = z;
    }

    void HienThi() {
        cout << "   Gia tri cua a la: " << a << endl;
        cout << "   Gia tri cua b la: " << b << endl;
        cout << "   Gia tri cua *p la: " << *p << endl;
    }
};

int main() {
    TestShallowCopy t1;
    t1.TaoDuLieu(2, 6, 8);
    TestShallowCopy t2 = t1;
    cout << "Du lieu cua doi tuong t1: " << endl;
    t1.HienThi();
    cout << "Du lieu cua doi tuong t2: " << endl;
    t2.HienThi();
    return 0;
}




```













</details>





**Destructor**
- Destructor dùng để hủy đối tượng.
- Destructor sẽ có tên trùng với tên của class và thêm ký tự ~ ở phía trước tên.
- Chỉ có duy nhất một hàm hủy trong một lớp. Hàm hủy tự động được gọi. Nếu như chúng ta không định nghĩa hàm hủy thì mặc định trình biên dịch sẽ tự tạo ra một hàm hủy mặc nhiên
- Hàm hủy (Destructor) trong C++ được gọi tự động khi:
	+ Kết thúc hàm
	+ Kết thúc chương trình
	+ Toán tử delete được gọi
- Destructor dùng để giải phóng tài nguyên mà đối tượng sở hữu

<details>
<summary>Ví dụ:</summary>

```C++
#include <iostream>  
using namespace std;  
class NhanVien  {  
   public:  
        NhanVien() {    
            cout << "Ham xay dung duoc goi" << endl;    
        }    
        ~NhanVien() {    
            cout << "Ham huy duoc goi" << endl;    
        }  
};  
int main(void) {  
	NhanVien* n0 = new NhanVien();
	delete n0;
    NhanVien n1;   
    NhanVien n2; 
    return 0;  
}

```
</details>

**Vitual Destructor**

- virtual destructor nằm ở lớp cha( lớp cơ sở ), khi ta có 1 đối tượng của lớp con  được tạo ra và xóa từ con trỏ của lớp cha.Destructor của cả lớp con  và lớp cha đều được gọi, đảm bảo rằng tất cả các tài nguyên được giải phóng đúng đắn.

<details>
<summary>Ví dụ:</summary>

```C++
#include <iostream>

class Base {
public:
    virtual ~Base() {
        std::cout << "Base destructor" << std::endl;
    }
};

class Derived : public Base {
public:
    ~Derived() {
        std::cout << "Derived destructor" << std::endl;
    }
};

int main() {
    Base* ptr = new Derived(); // Tạo một đối tượng Derived và gán con trỏ của lớp cơ sở
    delete ptr; // Xóa đối tượng thông qua con trỏ của lớp cơ sở

    return 0;
}


```
</details>

**Static keyword:property**
- Khi một property trong class được khai báo với từ khóa static, thì tất cả các object được tạo ra từ class đó sẽ dùng chung địa chỉ của property này.
- trước khi dùng Static phải khởi tạo giá trị cho nó  bên ngoài class:`KieuDuLieu TenLop::tenTruongStatic = Gia tri;`
- Dùng biến Static để tiết kiệm bộ nhớ ,vì các đối tượng trong cùng một lớp truy cập vào một biến static, nó đang chia sẻ vùng nhớ lưu trữ cho biến static đó
- Truy cập vào biến Static mà không cần tạo object

<details>
<summary>Ví dụ:</summary>

```C++
#include <iostream>  
using namespace std;  
class NhanVien { 
    int msnv;    
    string ten;
    int tuoi;
    public:  
       static string tenCongTy;
       NhanVien(int msnv, string ten, int tuoi) {    
            this->msnv = msnv;    
            this->ten = ten;    
            this->tuoi = tuoi; 
       }    
       void HienThi() {    
            cout << ten << endl;
            cout << "   Ma so nhan vien: " << msnv << endl;
            cout << "   Tuoi: " << tuoi << endl;
            cout << "   Ten cong ty: " << tenCongTy << endl;
       }    
};  
 
string NhanVien::tenCongTy = "TNHH Tin Hoc";
 
int main() {  
    NhanVien n1 =  NhanVien(111231, "Nguyen Van A", 25);    
    NhanVien n2 =  NhanVien(213214, "Nguyen Van B", 40);
    NhanVien n3 =  NhanVien(213215, "Nguyen Van C", 67);
    n1.HienThi();    
    n2.HienThi();
    n3.HienThi();
    return 0;  
}

```
</details>

**Static keyword:method**
- Tiện lợi và linh hoạt :
	+ gọi  static method từ bất kỳ nơi nào trong chương trình và không cần tạo object khi gọi 
-  truy cập được vào biến thành viên static, không thể truy cập vào biến thường
-  static method không thể gọi trực tiếp từ các methodc không static của lớp

<details>
<summary>Ví dụ:</summary>

```C++
#include <iostream>

class MyClass {
public:
    static int staticVariable; // Biến thành viên static

    // Phương thức static - Đặc điểm 1 và 2
    static void staticMethod() {
        std::cout << "This is a static method." << std::endl;
    }

    // Phương thức static truy cập vào biến thành viên static - Đặc điểm 3
    static void printStaticVariable() {
        std::cout << "Static variable value: " << staticVariable << std::endl;
    }

    // Phương thức static không thể truy cập biến thành viên không static - Đặc điểm 2
    /*
    static void printNonStaticVariable() {
        std::cout << "Non-static variable value: " << nonStaticVariable << std::endl;
    }
    */

    // Phương thức static không thể gọi từ phương thức không static - Đặc điểm 4
    /*
    void callStaticMethodFromNonStaticMethod() {
        staticMethod(); // Lỗi biên dịch
    }
    */
};

// Khởi tạo biến thành viên static
int MyClass::staticVariable = 42;

// Phương thức static có thể gọi từ bất kỳ nơi nào trong chương trình thông qua hàm - Đặc điểm 5
void callStaticMethodFromOutsideClass() {
    MyClass::staticMethod();
}

int main() {
    // Gọi phương thức static từ bên ngoài lớp
    callStaticMethodFromOutsideClass();

    // Gọi phương thức static từ bên trong lớp
    MyClass::printStaticVariable();


    return 0;
}

```

</details>


**Con trỏ this trong C++**
- This là một con trỏ đặc biệt dùng để trỏ đến địa chỉ của đối tượng hiện tại
- Trong ví dụ dưới thì đối tượng hiện tại là n1, n2
- Khi nào nên dùng con trỏ this:
	+ Nó có thể được sử dụng để truyền đối tượng hiện tại làm tham số cho method khác
	+ Khi gọi method từ các đối tượng khác nhau, nó sẽ trỏ tới địa chỉ của các đối tượng tương ứng.
- Trong trường hợp ta đặt tên của tham số method trùng tên với property, và gán property = tham số method, thì lúc này chương trình hiểu rằng đang gán giá trị của các tham số cho chính các tham số đó. Nên các property giữ giá trị mặc định của chúng (0) khi được tạo ra.
- Khi bạn sử dụng this->, bạn đang xác định rõ ràng rằng các phép gán áp dụng cho các proberty, không phải là các tham số của phương thức.

```c++
void setData(int msnv, string ten, int tuoi) {  
    this->msnv = msnv;    
    this->ten = ten;    
    this->tuoi = tuoi; 
}
```


<details>
<summary>Ví dụ:</summary>

```c++
#include <iostream>  
using namespace std;  
class NhanVien { 
    int msnv;    
    string ten;
    int tuoi;
    public:  
       void setData(int msnv, string ten, int tuoi) {  
            this->msnv = msnv;    
            this->ten = ten;    
            this->tuoi = tuoi; 
       }    
       void showData() {
            cout << "Ten nhan vien: " << this->ten << endl;
            cout << "Ma so nhan vien: " << this->msnv << endl;
            cout << "Tuoi: " << this->tuoi << endl;
       }    
};

int main() { 
    // Nhan vien 1
    NhanVien n1;
    n1.setData(111231, "Nguyen Van A", 24);
    n1.showData();    
     
    // Nhan vien 2
    NhanVien n2 =  NhanVien();
    n2.setData(111232, "Nguyen Van B", 25);
    n2.showData();
    return 0;  
}

```

</details>



<details>
<summary>Ví dụ:</summary>

```C++
#include <iostream>

class MyClass {
public:
    void printAddress() {
        std::cout << "Address of current object: " << this << std::endl;
    }
};

int main() {
    MyClass obj1;
    MyClass obj2;
    obj1.printAddress(); // In địa chỉ của đối tượng obj1
    obj2.printAddress(); // In địa chỉ của đối tượng obj2
    return 0;
}



```

</details>




<details>
<summary>Ví dụ:</summary>

```C++
class sinhvien {
	puplic:// phạm vi truy cập
	string ten;//PROPERTY
	int tuoi;
	int mssv;
	void display(){//METHOD
	count<<"ten:"<<ten<<endl;
	count<<"tuoi:"<<tuoi<<endl;
	count<<"mssv:"<<mssv<<endl;

}
};

int main(){
	sinhvien sv1;
	sv1.ten ="hoang";//OBJECT thuộc class sinh viên
	sv1.tuoi=19;
	sv1.mssv =123123;
	sv1.display();// in ra 0.
	return 0;

}

```
- Class có thể khởi tạo giá trị ban đầu:
```C++
class sinhvien {
	puplic:// phạm vi truy cập
	sinhvien(string l_ten , int l_tuoi,string l_lop, int l_ngay){// gia tri ban đầu có tham số đầu vào
		static int  s_mssv;
		mssv=s_mssv;
		s_mssv ++;
		tuoi =l_tuoi;
		ten=l_ten;
		lop=l_lop;
		ngay =l_ngay;
	}
	string ten;//PROPERTY
	stactic int ngay; // static trong class phải khởi tạo giá trị ban đầu 
	int tuoi;
	int mssv;
	string lop;
	string ten;
	void display();//METHOD
	
	//director là 1 cơ chế tự động 
	~sinhvien(){
		count<<"Huy object co ten:"<<ten>>endl;
	}
};

int sinhvien::ngay;// khởi tạo gia trị ban đầu cho static

void sinhvien::display{
	count<<"ten:"<<ten<<endl;
	count<<"tuoi:"<<tuoi<<endl;
	count<<"mssv:"<<mssv<<endl;
	ount<<"lop:"<<mssv<<endl;

}
void test1(){
	sinhvien sv1("thai",19,"CDEE"),sv2("tha",20,"fhsjd",14);//sv1 là OBJECT thuộc class sinhvien
	printf("dia chi sv1.mssv: %p\n",&(sv1.mssv));//khác địa chỉ
	printf("dia chi sv2.mssv: %p\n",&(sv2.mssv));//khác địa chỉ
	printf("--------------");
	printf("dia chi sv1.ngay: %p\n",&(sv1.ngay));//cung  địa chỉ
	printf("dia chi sv2.ngay: %p\n",&(sv2.ngay));//cung địa chỉ
	// Khi khởi tạo thì địa chỉ của nó tồn tại trong suốt chương trình nên member static này của các object sẽ đều có cùng 1 địa chỉ.
	sv1.display();
	sv2.display();	
}

int main(){
	test1();
	return 0;
	// sẽ in ra là ten,tuoi,mssv,lop,Huy object co ten thai
}
```

</details>
</details>














<details>
  <summary><h2>Smart Pointer</h2></summary>

**Cấp phát động trong C++**
- new và delete là hai toán tử quan trọng trong C++ được sử dụng để cấp phát và giải phóng bộ nhớ động, tương ứng

```C++
int *ptr = new int; // cấp phát bộ nhớ cho một biến kiểu int
int *arr = new int[5]; // cấp phát bộ nhớ cho một mảng kiểu int với 5 phần tử

delete ptr; // giải phóng bộ nhớ của biến động
delete[] arr; // giải phóng bộ nhớ của mảng động


```
**Smart Pointer C++**
- smart pointers là một cơ chế quản lý bộ nhớ tự động , tự động giải phóng vùng nhớ khi không còn bất kỳ smart pointer nào nắm giữ  vùng nhớ đó.Dựa vào cơ chế Destructer trong class

**Unique Pointer**
- unique_ptr là một loại smart pointer trong C++, Cơ chế của nó cho phép  một smart pointer sở hữu vùng nhớ và khi smart pointer này bị hủy, vùng nhớ cũng sẽ được giải phóng.Sẽ tự động giải phóng vùng nhớ khi ra khỏi phạm vi của nó,phạm vi của nó có thể là kết thúc 1 hàm con hoặc kết thúc chương trình , nếu nằm ở hàm main()

```C++
#include <iostream>
#include <memory>

void func() {
    std::unique_ptr<int> uniquePtr(new int(42));
    // uniquePtr sẽ tự động giải phóng vùng nhớ khi ra khỏi hàm func()
}

int main() {
    func();
    // uniquePtr đã bị giải phóng khi ra khỏi hàm func()
    return 0;
}

```
**shared_ptr**
- shared_ptr : Cớ chế của shared_ptr 1 biến(hoặc 1 vùng nhớ)  được nhiều Smart Pointer sỡ hữu , Smart Pointer này chỉ giải phóng khi không còn shared_ptr trỏ đến .Nó sử dụng một biến đếm tham chiếu để theo dõi số lượng các smart pointer đang trỏ đến đối tượng và giữ vùng nhớ được quản lý cho đến khi không còn smart pointer nào trỏ đến nó nữa.
- Ví dụ có 2 shared_ptr  trỏ đến 1 biến việc giải phóng vùng nhớ sẽ chỉ xảy ra khi cả hai shared_ptr này đều bị hủy hoặc không còn trỏ đến vùng nhớ nữa

```C++
#include <iostream>
#include <memory>

int main() {
    // Khởi tạo một biến int x với giá trị 42
    int x = 42;

    // Tạo ba shared_ptr để trỏ đến biến int x
    std::shared_ptr<int> sharedPtr1 = std::make_shared<int>(x);
    std::shared_ptr<int> sharedPtr2 = sharedPtr1;
    std::shared_ptr<int> sharedPtr3 = sharedPtr1;

    // In ra địa chỉ của x và số lượng tham chiếu của mỗi shared_ptr
    std::cout << "Địa chỉ của x: " << &x << std::endl;
    std::cout << "sharedPtr1: " << sharedPtr1.use_count() << std::endl;
    std::cout << "sharedPtr2: " << sharedPtr2.use_count() << std::endl;
    std::cout << "sharedPtr3: " << sharedPtr3.use_count() << std::endl;

    return 0;
}


```

**weak_ptr**
- weak_ptr là 1 smart pointer  không tham gia vào việc giải phóng vùng nhớ trực tiếp.
- Nó chỉ là một công cụ để theo dõi xem một đối tượng có tồn tại hay không mà không tăng số lượng tham chiếu đếm của nó. 
- weak_ptr có một phương thức là lock(). Nếu shared_ptr mà weak_ptr theo dõi vẫn tồn tại, lock() sẽ trả về một shared_ptr hợp lệ có thể sử dụng để truy cập đối tượng. Ngược lại, nếu shared_ptr đã bị giải phóng, lock() sẽ trả về một shared_ptr rỗng.






</details>
<details>
  <summary><h2>namespace</h2></summary>

- Namespace:là từ khóa trong C++ được sử dụng để phân biệt các hàm, lớp, biến cùng tên trong các file khác nhau.
 tạo những vùng nhớ khác nhau ,mỗi namespace là 1 chương trình riêng ,với 2 namespace khác nhau có thể tạo các biến trùng tên. Nhưng trong 1 namespace không thể có 2 biến cùng tên

<details>
<summary>Ví dụ:</summary>

```C++
//fileB.hpp

#include <iostream>

using namespace std;

namespace fileB{
    void function(() { cout << “function in fileB running.” << endl; }
}
//fileC.hpp
#include <iostream>

using namespace std;

namespace fileC{
    void function(() { cout << “function in fileC running.” endl; }
}


# 

```
**Dùng using namespace tên, có thể rút gọn code**
- Ví dụ:
```C++
using namespace onga;
int main(){
	cout<<"con ong a: teo"<<teo<<endl;
	return 0;
	
}

// FILE MAIN.CPP
#include <iostream>
#incldue “fileB.hpp”
#include “fileC.hpp”

using namespace std;

int main() {
    fileB::function();
    fileC::function();
    
    return 0;
}

 

```

</details>
</details>
<details>
  <summary><h2>Lambda,templates</h2></summary>

**Lambda**
- Lambda là một cú pháp trong ngôn ngữ lập trình C++ cho phép tạo ra các hàm vô danh (anonymous functions) ngắn gọn và linh hoạt ngay tại chỗ mà không cần phải đặt tên  cho chúng,Cú pháp của lambda rất linh hoạt và có thể được sử dụng để viết mã ngắn gọn và dễ đọc.
- Cú pháp :
` [capture clause] (parameter list) -> return type { body }`
- Capture clause: Là cách bạn chọn để capture các biến từ phạm vi bên ngoài vào bên trong lambda. Có thể capture bằng reference (&), capture bằng giá trị (=), hoặc không capture ([]).
- parameter list: Là danh sách các tham số của hàm lambda, tương tự như danh sách tham số của một hàm thông thường.
- return type: Là kiểu dữ liệu của giá trị trả về của hàm lambda. Trong một số trường hợp, trình biên dịch có thể tự suy luận kiểu dữ liệu này.
- body: Là phần thân của hàm lambda, nơi  viết mã lệnh thực thi các công việc của hàm.
- Trong C++, có ba cách chính để capture các biến từ phạm vi bên ngoài vào trong một lambda function:
	+	Capture bằng Giá Trị (=):
		+ Capture tất cả các biến được sử dụng trong lambda theo cách sao chép giá trị của chúng.
		Các biến được capture bằng giá trị sẽ không thay đổi giá trị của chúng ngoài lambda khi chúng được thay đổi trong lambda.
	+	Capture bằng Reference (&):
		+ Capture tất cả các biến được sử dụng trong lambda theo cách tham chiếu đến chúng.
		+ Các biến được capture bằng reference cho phép thay đổi giá trị của chúng ngoài lambda khi chúng được thay đổi trong lambda.
	+ Capture Tự Do (không sử dụng capture clause):
		+ Không capture bất kỳ biến nào từ phạm vi bên ngoài vào trong lambda.
		+ Lambda chỉ có thể truy cập các biến được định nghĩa trong lambda hoặc các biến toàn cục.
**Lambda function mang lại tính ngắn gọn và linh hoạt trong việc viết code, giúp tăng cường độ dễ đọc và dễ bảo trì của chương trình**

**Template**
- Là một kiểu dữ liệu trừu tượng tổng quát hóa cho các kiểu dữ liệu int, float, double, bool...cho phép  viết mã một cách tổng quát cho nhiều loại dữ liệu khác nhau mà không cần phải viết lại mã nhiều lần
- Có 2 loại  Templates:
	+ Class Templates: cho phép proberti và method trong Class có kiểu dữ liệu template, lúc này trong hàm chính , tùy mục đích có thể đặt kiểu dữ liệu(int ,double..) cho class và object sẽ có kiểu DL theo class
	+ Function templates:Function templates cho phép bạn tạo ra các hàm mà có thể làm việc với nhiều kiểu dữ liệu khác nhau. Bạn chỉ cần viết một hàm mẫu (template) và sau đó sử dụng nó để tạo ra các phiên bản cụ thể cho mỗi kiểu dữ liệu mà bạn muốn sử dụng.

```C++
	// Khai báo một class template cho một cặp giá trị
	template <class T, class U>
	class Pair {
	public:
		T first;
		U second;
		Pair(T a, U b) : first(a), second(b) {}
	};
	int main() {
		Pair<int, double> p1(1, 3.14);
		std::cout << "First: " << p1.first << ", Second: " << p1.second << std::endl;

		Pair<std::string, char> p2("Hello", 'X');
		std::cout << "First: " << p2.first << ", Second: " << p2.second << std::endl;

    return 0;
}
	// Hàm template tính tổng của hai giá trị
	template <class T>
	T sum(T a, T b) {
		return a + b;
	}
	int main() {
    std::cout << "Sum of integers: " << sum(5, 10) << std::endl; // T được suy luận là int
    std::cout << "Sum of doubles: " << sum(3.14, 2.5) << std::endl; // T được suy luận là double
    

    return 0;
}

```
	

**Virtual Function**
- Hàm ảo , cho phép hàm của lớp con ghi đè lên hàm lớp cha






</details>
<details>
<summary><h3>Hướng đối tượng </h3></summary>

### hướng đối tượng là gi?
- OOP là một phương pháp lập trình dưới dạng các "đối tượng," mỗi đối tượng có chứa dữ liệu và các phương thức để thao tác dữ liệu đó.
- Các khái niệm quan trọng trong OOP bao gồm:
	+ Class: để tạo ra các đối tượng , nó mô tả dữ liệu và phương thức của đối tượng đó
	+ Đối tượng (Object) : Một đối tượng cụ thể được tạo ra từ class, có 
**Phạm vi truy cập:**
- Public:Member nào trong Public thì có thể truy cập từ mọi nơi trong chương trình , bao gồm object của lớp và từ các lớp khác thông qua method của lớp đó, có thể truy cập được
- protected:Member trong protected thì method của Class con và method trong class có thể truy cập
- private: Chỉ có method  trong class có thể truy cập .

```c++
#include <iostream>

class ClassA {
public:
    int publicVarA;

    ClassA() : publicVarA(0) {}
};

class ClassB {
public:
    void accessPublicVar(ClassA &objA) {
        std::cout << "Value of publicVarA from ClassB: " << objA.publicVarA << std::endl;
    }
};

int main() {
    ClassA objA;
    ClassB objB;

    objA.publicVarA = 42; // Gán giá trị cho thành viên publicVarA của đối tượng objA

    objB.accessPublicVar(objA); // Truy cập thành viên publicVarA của đối tượng objA từ đối tượng objB

    return 0;
}






```

**1/Encapsulation (Tính đóng gói):**
- PROPERTY phải nằm ở private hoặc protected.
- Lý do để bảo vệ dữ liệu của một đối tượng khỏi sự xâm phạm từ bên ngoài.

<details>
<summary>Ví dụ:</summary>

```C++
#include<iostream>
#include<string>
using namespace std;
class doituong{
	private:
	int tuoi;//PROPERTY
	string ten;

	public:
	void hienthi(){//hienthi() method
	    cout<<"ten: "<<ten<<endl;
		cout<<"tuoi: "<<tuoi<<endl;
	}
	void setten(int name){
		ten=name;
	}
	void settuoi(int old){
		tuoi=old;
	}
	int gettuoi(){
		return tuoi;

	}
	string getten(){
		return ten;

	}
	

}
int main(){
	doituong dt;//dt là object thuộc class doituong
	dt.hienthi();
	return 0;
 }
```
</details>

**2/Inheritance (Tính kế thừa ):**
- Một class có thể kế thừa các thuộc tính của một class khác đã tồn tại trước đó.Để kế thừa từ class khác, ta dùng ký tự “ : ”.Khi một class con được tạo ra bởi việc kế thừa thuộc tính của class cha thì chúng ta sẽ gọi class con đó là subclass trong C++, và class cha chính là superclass trongC++.
- Class con có thể kế thừa property và method của class cha trong phạm vi public và protected  
- Có 3 kiểu kế thừa là public, private và protected. Những property và method được kế thừa từ class cha sẽ nằm ở quyền truy cập của class con tương ứng với kiểu kế thừa.

- Nên dùng: Khi một lớp B được miêu tả là "B là một A". Ví dụ: một lớp hình tròn có thể kế thừa từ một lớp hình học.
- Không nên:Mối quan hệ "has-a" (có một) diễn ra khi một lớp chứa một đối tượng của một lớp khác. ví dụ: danhsachSV chứa một đối tượng sinhvien, do đó chúng ta có thể nói danhsachSV "có" hoặc "bao gồm" danh sách các sinh viên.

<details>
<summary>Ví dụ:</summary>

```C++
using namespace std;

class doituong{

	protected:
	int namsinh;
	string ten;
	int tuoi;
	public:
	void nhapthongtin(string name,int old,int year){ 
	    	ten=name;
			tuoi=old;
			namsinh=year;
	}
	void hienthi(){//hienthi() method cha
	    	cout<<"ten: "<<ten<<endl;
			cout<<"tuoi: "<<tuoi<<endl;
			cout<<"namsinh: "<<namsinh<<endl;
	}

};

class sinhvien : public doituong{
    protected:
	int MSSV;
	public:
	void setMSSV(int mssv){
		MSSV=mssv;
	}
	void hienthi(){// là method con từ cha và sửa nó thì được gọi là override(ghi đè)
		cout<<"MSSV: "<<MSSV<<endl;
		cout<<"ten: "<<ten<<endl;
		cout<<"tuoi: "<<tuoi<<endl;
		cout<<"namsinh: "<<namsinh<<endl;
		

	}

};


class HS : public sinhvien{
    private:
	int HS;
	public:
	void setHS(int hs){
		HS=hs;
	}
	void hienthi();

};
//thằng HS sẽ kế thừa thằng gần nhất >> hienthi(), sẽ kế thừa hienthi() của sinhvien chứ không phải doituong
int main(void){
    doituong dt;
	sinhvien sv;
	dt.nhapthongtin("hung",24,1883);
	dt.hienthi();
	printf("-----------\n");
	sv.nhapthongtin("thai",25,1992);
	sv.hienthi();

    return 0;
}
//ten: hung
//tuoi: 24
//namsinh: 1883
-----------
//MSSV: 0
//ten: thai
//tuoi: 25
//namsinh: 1992

```
</details>


<details>
<summary>Ví dụ:</summary>

```C++
class doituong{
	protected:
	int namsinh;
	string ten;
	int tuoi;
	public:
	void nhapthongtin(string name,int old,int year){ 
	    	ten=name;
			tuoi=old;
			namsinh=year;
	}

};

class sinhvien : private doituong{	
	// tất cả property  của doituong sẽ chuyển vào private của sinhvien
 

};

class hs : private sinhvien{
 // lỗi vì thằng private không kế thừa và sử dụng được từ class con
};

```

</details>

**3/Polymorphism (Tính đa hình):**
- Các method có thể trùng tên với nhau , nhưng phải khác các input parameter
<details>
<summary>Ví dụ:</summary>

```C++
using namespace std;

class ToanHoc {
public:
    void tong(int a, int b) {
        cout << "Tong a + b: " << a + b << endl;
    }

    void hienthi(int a, int b, int c) {
        cout << "Tong a + b + c: " << a + b + c << endl;
    }

    void hienthi(int a, double b) {
        cout << "Tong a + b : " << a + b << endl;
    }
};

int main() {
    ToanHoc th;
    th.tong(7, 4);
    th.hienthi(1,2,3);
    th.hienthi(1,1.1);
     

    return 0;
}
```
</details>

**4/Abstraction (Tính trừu tượng ):**

- Ẩn đi những thành phần tạo ra đối tượng .chỉ hiển thị những gì cần thiết để sử dụng đối tượng đó, tức là các method mà người sử dụng bên ngoài có thể truy cập và tương tác.
- Ví dụ tính phương trình bậc 2 , để tính nghiệm x1,x2 thì ta có hàm tính detal = b * b - 4 * a * c .delta là 1 trong những thành phần tạo ra kết quả.Vậy thì hàm tính delta này phải được ẩn đi bằng cách để nó vào phạm vi private

<details>
<summary>Ví dụ:</summary>

```C++
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class GiaiPhuongTrinh
{
private:
    double a;
    double b;
    double c;
    double x1;
    double x2;
    double delta;

    void tinhNghiem()
    {
        delta = b * b - 4 * a * c;
        if (delta < 0)
        {
            delta = -1;
        }
        else if (delta == 0)
        {
            x1 = x2 = -b / (2 * a);
        }
        else if (delta > 0)
        {
            x1 = (-b + sqrt(delta)) / (2 * a);
            x2 = (-b - sqrt(delta)) / (2 * a);
        }
    }

public:
    void enterNumber(double num_a, double num_b, double num_c);
    void printResult();
};

void GiaiPhuongTrinh::enterNumber(double num_a, double num_b, double num_c)
{
    a = num_a;
    b = num_b;
    c = num_c;
}

void GiaiPhuongTrinh::printResult()
{
    tinhNghiem();
    if (delta == -1)
    {
        cout << "PT vo nghiem" << endl;
    }
    else if (delta == 0)
    {
        cout << "PT co nghiem chung: " << x1 << endl;
    }
    else if (delta > 0)
    {
        cout << "PT co 2 nghiem: \n";
        cout << "x1: " << x1 << endl;
        cout << "x2: " << x2 << endl;
    }
}

int main()
{
    GiaiPhuongTrinh phuongtrinh1;
    phuongtrinh1.enterNumber(1, 5, 4);
    phuongtrinh1.printResult();

    return 0;
}





```


</details>

**Hàm Bạn,Lớp Bạn?**
- Là các khái niệm cho phép một hàm hoặc một lớp khác có thể truy cập các thành viên private hoặc protected của một lớp.

**Template trong C++ là gì?**

- Là một kiểu dữ liệu trừu tượng tổng quát hóa cho các kiểu dữ liệu int, float, double, bool...
- Có 2 loại  Templates:
	+ Class Templates: cho phép proberti và method trong Class có kiểu dữ liệu template
	+ Function templates:cho phép viết một hàm với kiểu dữ liêu template , kiểu template sẽ tổng quát hóa nhiều kiểu dữ liệu khác, làm mã ngắn gọn hơn mà không cần triển khai lại hàm với kiểu dữ liệu cụ thể
		- Ví dụ 1 hàm có tham số truyền vào là int , int thì ta phải viết 1 hàm có cùng kiểu dữ liệu đó , nhưng nếu viết hàm dùng kiểu dữ liêu template, thì không cần quan tâm đến thông số truyền vào là kiểu dữ liệu gì

<details>
<summary>Ví dụ</summary>

```C++	
void hienthi(int a,int b ,int c){ 
		printf("tong a+b+c :%d\n",a+b+c);
}
int hienthi(int a,double b){ 		
		return a +(int)b;
}
//thay vì dài như vậy ta có thể dùng Template do C++ hỗ trợ
//Code viết lại:
template <typename test>
test tong(test a,test b){
	return test(a +b);
}
int main(void){
	tong("tong a va b: %d\n",tong(6,4));
	tong("tong a va b: %f\n",tong(6.5,4.4));
} 
```
</details>


**Virtual funtion trong C++ là gì?**
- Được sử dụng để tạo hàm ảo. Hàm ảo cho phép lớp con ghi đè hàm của lớp cha  . 


<details>
<summary>Ví dụ</summary>

```C++
#include <iostream>

// Lớp cha
class Base {
public:
    // Hàm ảo
    virtual void display() {
        std::cout << "This is a Base class method." << std::endl;
    }
};

// Lớp con kế thừa từ lớp cha
class Derived : public Base {
public:
    // Ghi đè (override) hàm ảo của lớp cha
    void display() override {
        std::cout << "This is a Derived class method." << std::endl;
    }
};

int main() {
    Derived obj;
    obj.display(); // Gọi phương thức display() của lớp con

    return 0;
}



```
</details>
</details>
<details>
  <summary><h2>Standard template library </h2></summary>

## STL là một thư viện trong ngôn ngữ lập trình C++ cung cấp một tập hợp các  hàm mẫu và thuật toán để lưu trữ và thao tác dữ liệu.

**Một số thành phần chính của STL:**
- Container(Bộ chứa)
- Một container là một cấu trúc dữ liệu chứa nhiều phần tử gồm:
	+ Vector
	+ List
	+ Map

- Iterator: Cung cấp 1 cách chung để duyệt các phần tử trong Container mà không cần quan tâm tới container đó là gi.
 - Trong STL, có nhiều loại iterators:
	+ Input Iterators: Cho phép duyệt qua các phần tử của một container từ đầu đến cuối, nhưng không thể thay đổi giá trị của các phần tử.
	+ Output Iterators: Cho phép ghi dữ liệu vào một container từ đầu đến cuối.
- Algorithms: STL cung cấp một loạt các thuật toán tiêu chuẩn như sort, find, binary_search, etc. Những thuật toán này có thể được áp dụng trên các containers.



**Vector trong C++ là gì?**

- vector là một mảng động,có thể mở rộng ,có thể chèn và xóa phần tử ở cuối mảng một cách hiệu quả
- Sử dụng Vector: Thêm hoặc xóa phần tử ở cuối danh sách
- Một số method của vector:
1. at(): Truy cập vào phần tử của vector
2. size(): Trả về kích thước của vector
3. resize(): Thay đổi kích thước của vector
4. begin(): Địa chỉ của phần tử đầu tiên của vector
5. end(): Địa chỉ của phần tử cuối cùng của vector
6. push_back(): Thêm phần tử vào vị trí cuối của vector

**Lish trong C++ là gì?**
- List: Là một danh sách liên kết , List cung cấp khả năng chèn và xóa phần tử ở bất kỳ vị trí nào 
- Khi cần thêm hoặc xóa phần tử ở bất kỳ vị trí nào trong danh sách
- Một số method của Lish:
1. push_back() và push_front(): Thêm một phần tử vào cuối hoặc đầu của danh sách.
2. pop_back() và pop_front(): Xóa phần tử cuối cùng hoặc đầu tiên của danh sách.
3. insert(): Chèn một phần tử vào vị trí cụ thể trong danh sách.
4. erase(): Xóa một hoặc nhiều phần tử từ danh sách dựa trên vị trí hoặc một khoảng vị trí.
5. size(): Trả về số lượng phần tử trong danh sách.

**Set trong C++ là gì?**
- Set: Là một container không cho phép phần tử trùng lặp và sắp xếp tự động các phần tử theo thứ tự tăng dần
- Khi cần sắp xếp tự động các phần tử theo thứ tự tăng dần hoặc giảm dần.
- Khi cần lưu trữ một tập hợp các phần tử duy nhất.
- Một số method của Set:
1. insert(): Chèn một phần tử vào set. Nếu phần tử đã tồn tại, nó sẽ không được chèn lại.
2. erase(): Xóa một hoặc nhiều phần tử từ set dựa trên giá trị hoặc iterator.
3. find(): Tìm kiếm một phần tử trong set và trả về iterator đến nó nếu nó tồn tại, hoặc end() nếu không tìm thấy.
4. size(): Trả về số lượng phần tử trong set.
5. empty(): Kiểm tra xem set có rỗng không.
6. clear(): Xóa tất cả các phần tử trong set.

**Map trong C++ là gì?**
- Là một container lưu trữ dữ liệu theo cặp key-value. Mỗi phần tử trong map được liên kết với một key duy nhất và một giá trị
- Cần ánh xạ (map) một giá trị (key) đến một giá trị khác (value), nơi mỗi key là duy nhất và không được phép trùng lặp.
- Một số method của Map:
1. insert(): Thêm một cặp key-value vào std::map. Nếu key đã tồn tại, giá trị tương ứng sẽ được cập nhật.
erase(): Xóa một phần tử từ std::map dựa trên key.
2. find(): Tìm kiếm một phần tử trong std::map dựa trên key. Trả về iterator đến phần tử nếu nó tồn tại, hoặc trả về end() nếu không tìm thấy.
3. size(): Trả về số lượng phần tử trong std::map.
 

<details>
<summary>Ví dụ </summary>

```C++
#include <iostream>
#include <vector>

using namespace std;

int main()
{
  
    vector <int> arr1 = {2,5,7,4,9};

    arr1.at(0) = 3;
    arr1.resize(7);

    for (int i = 0; i < arr1.size(); i++)
    {
        cout << "Value: " << arr1.at(i) << endl;
    }
    
    arr1.push_back(10);

    cout << "-----------" << endl;
    for (int i = 0; i < arr1.size(); i++)
    {
        cout << "Value: " << arr1.at(i) << endl;
    }
    

    return 0;
}

```

</details>

**List là gì**
- List là một c  danh sách liên kết hai chiều.
- Dưới đây là một số đặc điểm quan trọng của list:
	+ Truy cập tuần tự
	+ Hiệu suất chèn và xóa: 
- Một số method của list:
	+ push_back():
	+ pop_back():
	+ insert(): Chèn một node vào list
	+ erase(): Xóa một node của list
	+ size(): Trả về kích thước của list
- Sử dụng vector khi:
	+ Cần truy cập ngẫu nhiên đến các phần tử.
    + Thực hiện nhiều thao tác chèn/xóa ở cuối danh sách.
	+ Dung lượng có thể biết trước hoặc thay đổi ít.
- Sử dụng list khi:
	+ Thực hiện nhiều thao tác chèn/xóa ở bất kỳ vị trí nào trong danh sách.
	+ Cần thực hiện nhiều thao tác chèn/xóa mà không làm ảnh hưởng đến các iterators hiện có.

**Map**
- Map là một container trong STL của C++, cung cấp một cấu trúc dữ liệu ánh xạ key-value
- Map lưu trữ các phần tử dưới dạng cặp key-value, trong đó mỗi key phải là duy nhất trong map.
- Ta có thể thêm phần tử mới vào map bằng cách sử dụng operator [] hoặc hàm insert(). Để xóa phần tử, bạn có thể sử dụng hàm erase().
- Ta có thể sử dụng iterator để duyệt qua các phần tử của map

**Array**
- Array là một container có kích thước cố định và có sẵn trong thư viện STL (Standard Template Library)
- array có kích thước cố định được xác định tại thời điểm biên dịch và không thể thay đổi sau khi được khai báo.
- array hỗ trợ truy cập ngẫu nhiên vào các phần tử thông qua toán tử []

# Iterator
- Iterator cung cấp một cách chung để duyệt qua các phần tử của một container mà không cần biết chi tiết về cách container được triển khai.
- Iterator là một đối tượng cho phép truy cập tuần tự qua các phần tử của một container.
- Nó giống như con trỏ, cho phép di chuyển qua các phần tử trong container.

# Algorithm
- Thư viện STL (Standard Template Library) cung cấp một số thuật toán tiêu biểu thông qua algorithm. 
- Các thuật toán này hoạt động trên các phạm vi hoặc các loại dữ liệu khác nhau, giúp thực hiện các nhiệm vụ như sắp xếp, tìm kiếm, chuyển đổi dữ liệu, và nhiều thao tác khác. 















<details>
<summary>Ví dụ quan trọng</summary>

```C++
#include <iostream>
#include <string>
#include <vector>

#define in 0
#define intb 1
#define add 2
#define del 3
#define fix 4
#define rs 5
#define out 6


 

using namespace std;

class sinhvien {
protected:
    string tensv;
    int tuoisv;
    int idsv;
    float diemtoansv;
    float diemlysv;
    float diemhoasv;
    float diemtrungbinhsv;

public:
    sinhvien() : tuoisv(0), idsv(0), diemtoansv(0.0), diemlysv(0.0), diemhoasv(0.0), diemtrungbinhsv(0.0) {}

    sinhvien(string name, int old, int id, float diemtoan, float diemly, float diemhoa)
        : tensv(name), tuoisv(old), idsv(id), diemtoansv(diemtoan), diemlysv(diemly), diemhoasv(diemhoa) {}

    void nhapthongtinsv() {
        cout << "Nhap ten sinh vien: ";
        cin.ignore();
        getline(cin, tensv);

        cout << "Nhap tuoi sinh vien: ";
        cin >> tuoisv;

        do {
        cout << "Nhap diem toan sinh vien (0>>10): ";
        cin >> diemtoansv;
        } while (diemtoansv < 0 || diemtoansv >10 );
        
       

        do {
            cout << "Nhap diem ly sinh vien (0>>10): ";
            cin >> diemlysv;
        } while (diemlysv < 0 || diemlysv > 10);

        do {
            cout << "Nhap diem hoa sinh vien (0>>10): ";
            cin >> diemhoasv;
        } while (diemhoasv < 0 || diemhoasv > 10);
    }

    float diemtrungbinh() {
        diemtrungbinhsv = (diemtoansv + diemlysv + diemhoasv) / 3;
        return diemtrungbinhsv;
    }

    string layXepLoai()  {
        float dtb = diemtrungbinh();
        if (dtb > 8) {
            return "Gioi";
        } else if (dtb >= 6.5 && dtb < 8) {
            return "Kha";
        } else {
            return "TB";
        }
    }

    string layThongTin()  {
        return "Ten: " + tensv + "\nTuoi: " + to_string(tuoisv) + "\nID: " + to_string(idsv) +
               "\nDiem Toan: " + to_string(diemtoansv) + "\nDiem Ly: " + to_string(diemlysv) +
               "\nDiem Hoa: " + to_string(diemhoasv) + "\nDiem Trung Binh: " + to_string(diemtrungbinhsv) +
               "\nXep loai: " + layXepLoai();
    }

    int layIdSV()  {
        return idsv;
    }
    void setIdSV(int newId) {
        idsv = newId;
    }
 
};

class danhsachSV {
private:
    vector<sinhvien> danhsachsinhvien;
    static int maxId ;
    

public:
   
    void xoasv(int id) {
        int n = danhsachsinhvien.size();
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (danhsachsinhvien[i].layIdSV() == id) {
                found = true;
                // Xóa sinh viên tại vị trí i
                danhsachsinhvien.erase(danhsachsinhvien.begin() + i);
                cout << "Da xoa sinh vien co ID " << id << endl;

            break;  
            }   
        }  
        if (!found) {
        cout << "Khong tim thay sinh vien co ID " << id << endl;   
        }

    }

    void suaThongTinSV(int id) {
        int n = danhsachsinhvien.size();
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (danhsachsinhvien[i].layIdSV() == id) {
                found = true;
                cout << "Nhap thong tin moi cho sinh vien:\n";
                sinhvien svMoi;
                svMoi.nhapthongtinsv();
                svMoi.diemtrungbinh();
                danhsachsinhvien[i] = svMoi;
                cout << "Da cap nhat thong tin cho sinh vien co ID " << id << endl;

                break;  
            }
        }

        if (!found) {
            cout << "Khong tim thay sinh vien co ID " << id << endl;
        }
    }


    void sapXepTheoDiemTB() {
        int n = danhsachsinhvien.size();
        
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                 
                if (danhsachsinhvien[j].diemtrungbinh() > danhsachsinhvien[j + 1].diemtrungbinh()) {                  
                    sinhvien temp = danhsachsinhvien[j];
                    danhsachsinhvien[j] = danhsachsinhvien[j + 1];
                    danhsachsinhvien[j + 1] = temp;
                }
            }
        }
    }

    void inThongTinDanhSach() const {
        for (auto sv : danhsachsinhvien) {
            cout << sv.layThongTin() << endl;
            cout << "-------------" << endl;
        }
    }

    void nhapThemSV() {
        sinhvien sv;
        maxId++;
        sv.setIdSV(maxId);
        sv.nhapthongtinsv();
        sv.diemtrungbinh();
        danhsachsinhvien.push_back(sv);
    }
    
    void reset(){
        danhsachsinhvien.clear();


    }
};

int danhsachSV::maxId = 0;

int main() {
    danhsachSV dssv;
    int nhapkey;
    int i_id;
    
    int soluongsv;

    do {
        cout << "Nhap so luong sinh vien (khong duoc am): ";
        cin >> soluongsv;
    } while (soluongsv < 0);

    for (int i = 0; i < soluongsv; i++) {
        dssv.nhapThemSV();
    }
    do {
        cout << "Vui long lam theo huong dan: "<< endl;
        cout << "Nhap 0:In ra danh sach sinh vien "<< endl;
        cout << "Nhap 1:In ra danh sach sinh vien theo diem TB"<< endl;
        cout << "Nhap 2:them sinh vien va in ra theo diem TB"<< endl;
        cout << "Nhap 3:xoa sinh vien va in ra theo diem TB"<< endl;
        cout << "Nhap 4:sua sinh vien va in ra theo diem TB"<< endl;
        cout << "Nhap 5:reset chuong trinh"<< endl;
        cout << "Nhap 6:thoat chuong trinh"<< endl;
    
    
        cin >> nhapkey;
        switch (nhapkey)
        {
        case  in:
            cout << "Danh sach sinh vien:"<< endl;;
            dssv.inThongTinDanhSach();
            break;

        case  intb:
            dssv.sapXepTheoDiemTB();
            cout << "Danh sach sinh vien sau khi sap xep theo diem trung binh:"<< endl;;
            dssv.inThongTinDanhSach();
            break;

        case add:
            dssv.nhapThemSV(); 
            dssv.inThongTinDanhSach();  
            break;

        case del:
            cout << "vui long nhap id sinh vien can xoa:"<< endl;;
            cin >> i_id;
            dssv.xoasv(i_id);
            dssv.inThongTinDanhSach();  
            break;

        case fix:
            cout << "vui long nhap id sinh vien can sua:"<< endl;;
            cin >> i_id;
            dssv.suaThongTinSV(i_id); 
            dssv.inThongTinDanhSach();  
            break;
        case rs:
            cout << "reset tat ca du lieu" << endl;
            dssv.reset();
            break;
        case out:
            cout << "Thoat chuong trinh" << endl;
            break;
        
        default:
            cout << "Lua chon khong hop le. Vui long nhap lai"<< endl;
            break;
        }
    }
    while (nhapkey!=6);
 
    return 0;

}


```
</details>



</details>
<details>
  <summary><h2>Multithreading</h2></summary>

**Lập trình đa luồng (Multithreading):**
- Là việc sử dụng nhiều luồng đồng thời trong một chương trình để tăng hiệu suất và sử dụng tốt các tài nguyên hệ thống.Muốn sử dụng thì `#include <thread>`

**Synchronization Mechanisms (Cơ chế đồng bộ hóa):**
- Đồng bộ hóa: Là quá trình đảm bảo rằng các luồng hoạt động đồng bộ khi truy cập và thay đổi dữ liệu chia sẻ. 
- Cơ chế đồng bộ hóa: Là phương pháp được sử dụng để đạt được đồng bộ  giữa các luồng, bao gồm cơ chế locks,unlock,mutex.Muốn sử dụng cơ chế này thì `#include <mutex>`
- Mutex (Mutual Exclusion): được sử dụng để đồng bộ hóa truy cập vào các tài nguyên được chia sẻ giữa các luồng
- Để khóa một mutex, bạn cần sử dụng phương thức lock() của đối tượng mutex, và để mở khóa mutex, bạn sử dụng phương thức unlock(). 
- Cơ chế lock(),unlock() được sử dụng để khóa mutex.Việc khóa mutex trước và mở khóa mutex sau đảm bảo rằng chỉ có một luồng có thể truy cập vào dữ liệu chia sẽ giữa 2 luồng
- std::unique_lock: Cơ bản có tính năng giống lock(),unlock(). nghĩa là 1 thời điểm chỉ cho 1 luồng truy cập dữ liệu , nhưng việc unlock là tự động
- std::shared_lock:cho phép nhiều luồng đọc cùng một lúc.

<details>
<summary>Ví dụ unique_lock</summary>

```c++

#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int sharedData = 0;
void threadFunction() {
    std::unique_lock<std::mutex> lock(mtx); // Khóa mutex
    ++sharedData; // Truy cập và thay đổi biến dữ liệu được chia sẻ
    std::cout << "Thread " << std::this_thread::get_id() << ": sharedData = " << sharedData << std::endl;
} 
int main() {
    std::thread t1(threadFunction);
    std::thread t2(threadFunction);

    t1.join();
    t2.join();

    return 0;
}

```
</details>


**Concurrent Data Structures (Cấu trúc dữ liệu đồng thời)**
- Cấu trúc dữ liệu đồng thời: Là  cấu trúc hỗ trợ truy cập  dữ liệu từ nhiều luồng mà không cần sử dụng locks hoặc mutexes.
- condition_variable là  một cơ chế trong C++11 được sử dụng để đồng bộ hóa các luồng thông qua việc chờ đợi và thông báo về sự kiện xảy ra
- condition_variable cho phép một hoặc nhiều luồng chờ đợi cho một điều kiện nhất định trở thành đúng trước khi tiếp tục thực hiện công việc của mình.
- condition_variable được sử dụng kết hợp với một mutex để đảm bảo độ an toàn khi truy cập và thay đổi trạng thái của điều kiện.
- condition_variable có các hàm :notify_one(),notify_all(),wait()
- thread1 chạy và tăng giá trị của biến count mỗi lần lặp. Khi count đạt đến 5, nó gửi một tín hiệu thông báo cho thread2 bằng cách gọi cv.notify_one().
thread2 chạy và đợi cho đến khi count đạt đến 5 trước khi tiếp tục thực hiện công việc của mình. Nó sử dụng cv.wait() để chờ đợi tín hiệu từ thread1.

**Bất đồng bộ (Asynchronous):**
- Trong lập trình, bất đồng bộ thường ám chỉ việc thực hiện một tác vụ mà không cần chờ đợi kết quả của tác vụ trước đó hoàn thành.
- Các tác vụ bất đồng bộ thường được thực hiện song song và có thể hoàn thành trong thời gian khác nhau.
- Bất đồng bộ thường được sử dụng trong các tình huống khi bạn muốn tiếp tục thực hiện các tác vụ khác mà không cần chờ đợi kết quả từ các tác vụ trước đó

<details>
<summary>Ví dụ quan trọng</summary>

```c++
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
int count = 0;

void thread1() {
    for (int i = 0; i < 5; ++i) {
        // Simulate some work
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        
        // Increase count
        {
            std::lock_guard<std::mutex> lock(mtx);
            ++count;
            std::cout << "Thread 1: Count = " << count << std::endl;
        }

        // If count reaches 5, notify thread 2
        if (count == 5) {
            cv.notify_one();
        }
    }
}

void thread2() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return count == 5; });
    std::cout << "Thread 2: Condition met, count = " << count << std::endl;
}

int main() {
    std::thread t1(thread1);
    std::thread t2(thread2);

    t1.join();
    t2.join();

    return 0;
}

```
</details>

**Task Parallelism (Song song hóa công việc):**

- Song song hóa công việc: Là phân chia một nhiệm vụ lớn thành các phần nhỏ và thực thi chúng song song trên nhiều luồng hoặc nhiều lõi CPU để tận dụng được sức mạnh tính toán của hệ thống.
- Điều này thường được sử dụng trong các ứng dụng đòi hỏi tính toán cao như xử lý hình ảnh, video, và tính toán khoa học.

**Challenges in Concurrency (Thách thức trong đồng thời hóa):**
- Race Conditions (Điều kiện cạnh tranh): Khi hai hoặc nhiều luồng cố gắng truy cập và thay đổi dữ liệu chia sẻ mà không có sự đồng bộ hóa, có thể dẫn đến kết quả không đoán trước được.
- Deadlocks (Mắc kẹt): Khi hai hoặc nhiều luồng đợi lẫn nhau để giải phóng tài nguyên mà họ cần, dẫn đến tình trạng tắc nghẽn không thể tiếp tục thực thi.
- Starvation (Đói đứng): Khi một hoặc nhiều luồng không thể tiếp tục thực thi vì chúng không nhận được tài nguyên hoặc quá trình lập lịch không công bằng.

</details>
</details>
</details>

</details>

</details>