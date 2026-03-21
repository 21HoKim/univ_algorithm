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