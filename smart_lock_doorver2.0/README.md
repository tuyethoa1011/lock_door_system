# smart_lock_door
Using STM32F411E to build smart lock door with function: Using password and ID card to unlock door. Further more, this smart lock door could let user configure new password for password mode. 

<br>

<h3>VER 1.0</h3>
<ul>
    <li>
        Các chức năng cũng như chế độ chưa hoàn thiện, dự tính sẽ xử lý đồng thời   
    </li>
    <li>
        Chỉ mới xử lý được keypad, nhập mật khẩu khóa cửa cho người dùng
    </li>
    <li>
        Xử lý khóa cửa bằng microservo SG90
    </li>
</ul>

<h3>VER 2.0</h3>
<ul>
    <li>
        Các chức năng mong muốn khóa cửa đã được thêm đầy đủ bao gồm 3 chế độ được note trong code
    </li>
    <li>
        Dự tính thay thế khóa điện từ thay cho microservo và thay việc xử lý 3 chế độ từ trên xuống dưới bằng cách xử lý đồng thời bằng FreeRTOS
    </li>
</ul>
