# Chương Trình Trao Đổi Khóa Diffie-Hellman
Chương trình này triển khai cơ chế trao đổi khóa Diffie-Hellman bằng C++. Nó thực hiện việc tạo số nguyên tố an toàn, tính toán khóa riêng và khóa công khai, và thiết lập khóa bí mật chung giữa hai bên: Alice và Bob.
## Tính Năng
1. Luỹ Thừa Modulo: Tính toán (base^exponent) % mod một cách hiệu quả bằng phương pháp bình phương và nhân.
2. Sinh Số Nguyên Tố Ngẫu Nhiên: Tạo ra số nguyên tố ngẫu nhiên có độ dài bit cố định (Thay đổi tuỳ ý).
3. Kiểm Tra Nguyên Tố: Sử dụng thuật toán Miller-Rabin để xác định số nguyên tố.
4. Trao Đổi Khóa Diffie-Hellman: Tạo khóa riêng và khóa công khai cho Alice và Bob, sau đó tính toán khóa bí mật chung.
## Cách sử dụng
> `git clone https://github.com/tientaiuu/CS15005-NhapMonMaHoa-Lab1.git`
## Kết quả 
Kết quả sẽ được lưu vào tệp ``` result.txt ``` với các thông tin chi tiết về thời gian chạy, số nguyên tố an toàn, khóa bí mật của Alice, khóa bí mật của Bob, và xác nhận hai khóa có bằng nhau hay không.

### Ví dụ kết quả
```		
					---- Result of Diffie Hellman key exchange - 512 bits ----

	Running Time: 19218.2 seconds

	Safe Prime Number: 11469947437460473449167012980905788174120151525485170145855375417364687142975626454821676528370140344092947009478331050001355513362517523473575629377238879

	Alice Secret: 4504482466590303690951139276747866661614944418588795513144599001721526490411976942211778861613184750425979246469234386651755028193135214926003805871361859

	Bob Secret: 4504482466590303690951139276747866661614944418588795513144599001721526490411976942211778861613184750425979246469234386651755028193135214926003805871361859

	Alice-Bob Secret equal? 1

```
Trong đó:
* Running Time: Thời gian chạy của chương trình.
* Safe Prime Number: Số nguyên tố an toàn *p* được tạo.
* Alice Secret và Bob Secret: Khóa bí mật chung được tính bởi Alice và Bob.
* Alice-Bob Secret equal?: Xác nhận khóa bí mật của Alice và Bob có bằng nhau không (1 là có, 0 là không).
