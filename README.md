# Специфікація:

Роздільники:

'\n', 'пробіл', 'кома', 'дужки', 'двокрапка'.

Параметри:

  - Координати - x0, x1, y0, y1 (0 - 100)
  - Висота - h (0 - 100)
  - Ширина - w (0 - 100)
  - Радіус - radius(0 - 100)
  - Колір - RGB(0 - 255)

Числові параметри представлені в десятковій системі числення.

Відповіді сервера на виконання команд:

  - Відповідь сервера при виконанні команди “Command Work!”

  - Відповідь сервера якщо команда не знайдена “Command not found!”

  - Відповідь сервера якщо недостатньо параметрів “Need More Parameters!”


Команди:

1. Очістка консолі:
clear display 255 255 255

2. Намалювати піксель:
draw pixel 1 1 255 255 255

3. Намалювати лінію:
draw line 1 1 2 2 255 255 255

4. Намалювати прямокутник:
draw rectangle 1 1 10 10 255 255 255

5. Заповнити прямокутник:
fill rectangle 1 1 10 10 255 255 255

6. Намалювати еліпс:
draw ellipse 1 1 10 10 255 255 255

7. Заповнити еліпс: 
fill ellipse 1 1 10 10 255 255 255

8. Намалювати коло:
draw circle 1 1 10 255 255 255

9. Заповнити коло:
fill circle 1 1 10 255 255 255

10. Намалювати прямокутник із закругленими угламі: 
draw rounded rectangle 1 1 20 20 10 255 255 255

11. Заповнити прямокутник із закругленими угламі:
fill rounded rectangle 1 1 20 20 10 255 255 255

12. Намалювати текст:
draw text 1 1 255 255 255 10 5 hello

13. Намалювати картінку:
draw image 1 1 10 10 'image.png'

14. Встановити орієнтацію полотна:
set orientation 90

15. Отримати ширину: 
get width

16. Отримати висоту:
get height
