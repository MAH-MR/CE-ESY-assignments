# CE-ESY-assignments 
تقدمة الطالب محمود مرعي
الرقم الامتحاني: 240313


المخزن الدائري هو عبارة عن مصفوفة ثابتة الحجم نهايتها متصلة ببدايتها.
تستخدم عادة لتخزين تدفق مستمر من البيانات حيث تتم القراءة والكتابة بشكل متزامن.
شرح عن الكود:
#include <stdio.h>
تم الاستدعاء للإدخاى والإخراج.
#include <string.h>
للتعامل مع النصوص.
#define CB_SIZE 16       
تحديد حجم المخزن ب 16 خانة.
#define CB_EMPTY '\0'    
يمثل الرمز الفارغ للإشارة إلى عدم وجود بيانات.



struct ConsoleBuffer {
 char      s[CB_SIZE];  
المصفوفة s التي ستخزن المحارف.
 unsigned int rpos;      
مؤشر القراءة.
 unsigned int wpos;     
مؤشر الكتابة. 
};



struct ConsoleBuffer cons_buf;

void cons_buf_init(void) {
 cons_buf.rpos = 0;
 cons_buf.wpos = 0;
}
دالة التهيئة، تقوم بتصفير مؤشرات القراءة والكتابة لبدء الاستخدام.



int cons_buf_is_empty(void) {
 return cons_buf.rpos == cons_buf.wpos;
}
التحقق من الفراغ، اذا كان مؤشر القراءة يساوي مؤشر الكتابة قهذا يعني انه لم تتم كتابة بيانات جديدة اوى تم قراءة كل ما كتب.



int cons_buf_is_full(void) {
 return (cons_buf.wpos - cons_buf.rpos) == (unsigned int)CB_SIZE;
}
التحقق من الامتلاء، يكون المخزن ممتلئاً اذا كان الفرق بين مؤشر القراءة والكتابة يساوي الحجم الكلي للمخزن.


char cons_buf_read(void) {
 if (cons_buf.rpos == cons_buf.wpos) {
     printf("[Underflow] Buffer is empty – nothing to read.\n");
     return CB_EMPTY;
 }

 return cons_buf.s[cons_buf.rpos++ & (CB_SIZE - 1)];
}
دالة القراءة، وتقوم بما يلي:
.تتحقق من وجود بيانات، اذا كان فارغاً يطبع "underflow"
.وإلا تقرا الحرف الحالي الموجود عند مؤشر القراءة وتقوم بزيادة مؤشر القراءة للمرة القادمة



void cons_buf_write(char c) {
 if (cons_buf_is_full()) {
     printf("[Overflow] Buffer full – oldest character '%c' discarded.\n",
            cons_buf.s[cons_buf.rpos & (CB_SIZE - 1)]);
     cons_buf.rpos++;
 }

 cons_buf.s[cons_buf.wpos++ & (CB_SIZE - 1)] = c;
}
دالة الكتابة، في حال overflow سيقوم البرنامج بالتخلص من أقدم حرف عن طريق زيادة مؤشر القراءة rpos.



int main(void) {
 char name[64];       
 char full_name[128]; 
 int  i;

 cons_buf_init();

 printf("Enter your name: ");
 fgets(name, sizeof(name), stdin);
طلب ادخال اسم المستخدم.

 name[strcspn(name, "\n")] = '\0';

 snprintf(full_name, sizeof(full_name), "%sCE-ESY", name);
دمج المدخل السابق مع CE-ESY.

 printf("Full string to buffer: \"%s\"\n", full_name);
 printf("Buffer size (CB_SIZE): %d\n\n", CB_SIZE);

 for (i = 0; full_name[i] != '\0'; i++) {
     cons_buf_write(full_name[i]);
 }

 printf("Output from buffer: ");
 while (!cons_buf_is_empty()) {
     putchar(cons_buf_read());
 }
 putchar('\n');

 if (cons_buf_is_empty()) {
     printf("\nBuffer is now empty. All characters consumed successfully.\n");
 }
اخيراً يطبع رسالة تؤكد أن المخزن اصبح فارغاً تماماً.

 return 0;
}
