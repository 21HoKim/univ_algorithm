.PHONY: FORCE
makefile: ;
Makefile: ;

ASan의 강력한 메모리 추적 기능을 직접 확인하셨군요. 콜스택(Call Stack) 분석은 물론, 섀도우 메모리(Shadow Memory) 맵을 통해 1바이트 단위의 오버플로우까지 시각화해 주는 매우 훌륭한 사이버보안 분석 도구입니다.

발생한 두 가지 문제(실행파일 미삭제, Git 원격 저장소 동기화)에 대한 원인과 해결책을 명확히 정리해 드립니다.

1. Makefile 실행파일 미삭제 문제 해결
test.c 실행 중 ASan이 메모리 결함을 탐지하고 커널에 SIGABRT (Abort) 시그널을 보내 프로세스를 비정상 종료시켰습니다. GNU Make는 레시피(Recipe) 실행 중 0이 아닌 종료 상태 코드(Non-zero Exit Status)가 반환되면 즉시 빌드 프로세스를 중단(Halt)시킵니다. 이 때문에 레시피 맨 마지막에 있던 @rm -f main 명령어가 실행되지 못하고 스킵된 것입니다.

이 문제를 해결하려면 쉘 스크립트 내부에서 **종료 상태 코드를 캡처(Capture)**한 뒤, 바이너리 삭제(Clean-up)를 먼저 수행하고 캡처해 둔 에러 코드를 Make에 다시 반환하도록 제어 흐름(Control Flow)을 수정해야 합니다.

Makefile의 내용을 아래 코드로 교체해 주세요. (명령어 앞 들여쓰기는 Tab 키 필수입니다.)

Makefile
.PHONY: FORCE

# Make 내부 자기 자신 컴파일 방지용 빈 레시피
makefile: ;
Makefile: ;

%.c: FORCE
	@echo "[1] 컴파일 진행 중: $@ (AddressSanitizer 및 디버깅 심볼 적용)"
	gcc $@ -o main -Wall -Wextra -g -fsanitize=address
	@if [ -f data/$*.in ] && [ -f data/$*.out ]; then \
		echo "[2] 자동 테스트 모드 진입 (제한 시간: 2초)"; \
		timeout 2s ./main < data/$*.in > data/$*.res; \
		STATUS=$$?; \
		if [ $$STATUS -eq 124 ]; then \
			echo "❌ 결과: 시간 초과 (Time Limit Exceeded) - 무한 루프가 의심됩니다!"; \
		elif [ $$STATUS -ne 0 ]; then \
			echo "❌ 결과: 런타임 에러 또는 메모리 결함 발생! (Exit Code: $$STATUS)"; \
			echo "   -> ⚠️ 위의 AddressSanitizer 에러 리포트를 확인하여 취약점을 패치하세요."; \
		else \
			diff -uw data/$*.out data/$*.res > /dev/null && echo "✅ 결과: 정답 (Pass)!" || (echo "❌ 결과: 출력 결과 불일치 (Wrong Answer)!"; diff -uw data/$*.out data/$*.res); \
		fi; \
		rm -f data/$*.res; \
		rm -f main; \
		exit $$STATUS; \
	else \
		echo "[2] 테스트 파일(data/$*.in, data/$*.out) 누락. 일반 실행 모드로 진입합니다."; \
		./main; \
		STATUS=$$?; \
		rm -f main; \
		exit $$STATUS; \
	fi