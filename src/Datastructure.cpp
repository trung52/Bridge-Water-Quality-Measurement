#include "Datastructure.h"
struct Node {
  String data;
  Node* next;
};

Node* head = NULL;
Node* tail = NULL;

int listSize = 0;

void addDataToList(String data) {
  Node* newNode = new Node;
  newNode->data = data;
  newNode->next = NULL;
  if (head == NULL) {
    head = newNode;
    tail = newNode;
  } else {
    tail->next = newNode;
    tail = newNode;
  }
  listSize++;
  
  if (listSize > 100) {
    Node* temp = head;
    head = head->next;
    delete temp;
    listSize--;
  }
}

void displayDataList(WiFiClient& client) {
  //client.println("<style>li { margin: 10px; }</style>"); // Thêm CSS để giảm khoảng cách giữa số thứ tự và nội dung
  //client.println("<ol type=\"1\" style=\"list-style-type: decimal;\">"); //not operate
  client.println("<ul style=\"list-style-type: none;\">"); 
  Node* current = head;
  int orderNumber=1;
  while (current != NULL) {
    client.print("<li>");
    client.print((String)orderNumber +". "+ current->data);
    client.println("</li>");
    current = current->next;
    orderNumber++;
  }
  client.println("</ul>"); 
}

//Using no_ota.csv partition, we have ~2MB for sketch and ~2MB for SPIFFS
void SPIFFS_saveStringDataToFile( String fileName_string, String fileContent_string){
  File writeFile;
  String locationFileSaveData = "/";
  locationFileSaveData = locationFileSaveData + fileName_string + ".csv"; //se truyen vao dataTime
  Serial.println("Writing file:" + locationFileSaveData);
  writeFile = SPIFFS.open(locationFileSaveData, FILE_APPEND);		// mo file de ghi du lieu
  if(writeFile){
    if(writeFile.println(fileContent_string)){
      Serial.println("File written successfully");
    } else {
      Serial.println("Write failed");
    }
    writeFile.close();
  }
  else{
    Serial.println("Failed to open file for writing");
    return;
  }
}

void SPIFFS_checkOutOfMemory() {
  size_t totalBytes = SPIFFS.totalBytes();
  size_t usedBytes = SPIFFS.usedBytes();

  // Tính toán sự chênh lệch
  size_t freeBytes = totalBytes - usedBytes;

  // Kiểm tra xem có cần xóa tệp không
  if (freeBytes <= 100 * 1024) { // 100KB

    // Mở thư mục SPIFFS
    File root = SPIFFS.open("/");

    // Lặp qua các tệp và xóa chúng (sẽ xóa các tệp cũ trước)
    while (File file = root.openNextFile()) {
      Serial.print("Deleting file: ");
      Serial.println(file.name());
      file.close();
      SPIFFS.remove(file.name());

      // Cập nhật lại dung lượng đã sử dụng
      usedBytes = SPIFFS.usedBytes();
      freeBytes = totalBytes - usedBytes;

      // Kiểm tra xem đã đạt đến điều kiện cần xóa đủ tệp chưa
      if (freeBytes > 100 * 1024) // Nếu đã đủ, thoát khỏi vòng lặp
        break;
    }
    root.close();
  }
}