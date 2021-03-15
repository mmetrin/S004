
#include <iostream>

int main()
{
	char string[256];
	char s[256] = "\n";

	//переменная, отвечающая за значение индекса начала копируемой подстроки
	int index;
	//переменная, отвечающая за длину копируемой подстроки
	int Len;
	//переменная, отвечающая за пустую строчку
	char EmptyString[] = " ";

	char f[] = "%s";
	char fd[] = "%d";

	std::cout << "Enter your string: ";
	char outStr1[256] = "Enter the index (start position of the copy): ";
	char outStr2[256] = "Enter the length of the copy: ";

	__asm
	{
		//помещаем ссылку на string в esi
		lea esi, string
		push esi

		lea ecx, f
		push ecx

		//ввод с консоли пользователем
		call scanf
		add esp, 8

		lea ebx, outStr1
		push ebx

		lea ecx, f
		push ecx

		//вывод на консоль данных 
		call printf
		add esp, 8

		lea ebx, index
		push ebx

		lea ecx, fd
		push ecx

		call scanf
		add esp, 8

		lea ebx, outStr2
		push ebx

		lea ecx, f
		push ecx

		call printf
		add esp, 8

		lea ebx, Len
		push ebx

		lea ecx, fd
		push ecx

		call scanf
		add esp, 8

		lea ecx, fd
		//кладем в регистр -1
		mov ecx, -1
		dec esi

		push edx
		mov edx, index

		lea ecx, fd
		mov ecx, -1
		dec esi

		lea ebx, string
		push ebx
		dec ebx

		//ниже происходит определение длины введенной строки 
		LengthOfString :

		//увеличиваем на 1 для задания шага цикла
		inc ecx
			inc ebx
			mov al, [ebx]
			cmp al, 0

			//переход если не равно
			jnz LengthOfString
			push ecx

			StartOfCopy :
		cmp index, 0

			//переход если больше или равно
			jge LengthCopy

			mov index, 0

			LengthCopy :
		cmp Len, 0

			//Переход если меньше
			jl StrNoChange

			FirstBiggerLength :
		cmp index, ecx

			//Переход если больше
			jg StrNoChange
			add edx, Len

			CheckLengthCopy :

		cmp edx, ecx
			jbe Later
			mov edx, ecx

			Later :
		add esp, 8

			mov ecx, -1
			dec esi

			lea esi, [string]
			lea edi, [s]

			push edi
			dec esi

			mov edx, index

			Write :
		inc esi
			inc ecx
			cmp ecx, edx

			//Переход если не равно
			jne Write
			add edx, Len



			ContinueWrite :
		inc ecx
			lodsb
			stosb

			cmp ecx, edx
			jne ContinueWrite

			jmp End



			StrNoChange :
		add esp, 8
			mov ecx, -1

			dec esi
			lea esi, [EmptyString]
			lea edi, [s]
			push edi



			ContinueNoChange :
		lodsb
			stosb
			cmp al, 0
			jnz ContinueNoChange

			End :
		pop edi
			pop esi
	}
	//выводим результирующую строку после удаления подстроки
	std::cout << "Result string: ";
	std::cout << s;
}

