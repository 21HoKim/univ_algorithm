.PHONY: FORCE data

# Make 내부 자기 자신 컴파일 방지용 빈 레시피
makefile: ;
Makefile: ;

# =====================================================================
# [기능 1] 테스트 데이터 스캐폴딩 (make data <파일명>)
# =====================================================================
# 명령줄의 첫 번째 단어가 'data'인지 확인
ifeq ($(firstword $(MAKECMDGOALS)),data)
  # 두 번째 단어(예: 4-1)를 추출하여 DATA_NAME 변수에 저장
  DATA_NAME := $(word 2, $(MAKECMDGOALS))
  # Make가 '4-1'을 타겟으로 착각하고 에러를 내지 않도록 빈 레시피로 동적 타겟 생성
  $(eval $(DATA_NAME):;@:)
endif

data:
	@if [ -z "$(DATA_NAME)" ]; then \
		echo "❌ 에러: 파일명을 입력하세요. (사용법: make data 4-1)"; \
	else \
		touch data/$(DATA_NAME).in data/$(DATA_NAME).out; \
		echo "✅ 테스트 셋 생성 완료: data/$(DATA_NAME).in, data/$(DATA_NAME).out"; \
	fi

# =====================================================================
# [기능 2] 자동 채점 및 AddressSanitizer 컴파일 (make <파일명.c>)
# =====================================================================
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
			diff -uw data/$*.out data/$*.res > /dev/null && echo "✅ 결과: 정답 (Pass)!" || \
			(echo "❌ 결과: 출력 결과 불일치 (Wrong Answer)!"; \
			echo "=================================================="; \
			echo " 🎯 정답 (Expected)"; \
			echo "--------------------------------------------------"; \
			cat data/$*.out; \
			echo ""; \
			echo "=================================================="; \
			echo " 💻 내 출력 (Actual)"; \
			echo "--------------------------------------------------"; \
			cat data/$*.res; \
			echo ""); \
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