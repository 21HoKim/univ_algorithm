.PHONY: FORCE data

# Make 내부 자기 자신 컴파일 방지용 빈 레시피
makefile: ;
Makefile: ;

# =====================================================================
# [기능 1] 테스트 데이터 스캐폴딩 (make data <파일명>)
# =====================================================================
ifeq ($(firstword $(MAKECMDGOALS)),data)
  DATA_NAME := $(word 2, $(MAKECMDGOALS))
  $(eval $(DATA_NAME):;@:)
endif

data:
	@if [ -z "$(DATA_NAME)" ]; then \
		echo "❌ 에러: 파일명을 입력하세요. (사용법: make data 4-1)"; \
	else \
		touch data/$(DATA_NAME).in data/$(DATA_NAME).out; \
		echo "✅ 테스트 셋 생성 완료: data/$(DATA_NAME).in, data/$(DATA_NAME).out"; \
	fi

# 확장자가 없는 타겟 이름이 들어왔을 때 .c 또는 .py 파일 존재 여부를 검사하여 분기(Branching)
%: FORCE
	@if [ -f $@.c ]; then \
		$(MAKE) $@.c; \
	elif [ -f $@.py ]; then \
		$(MAKE) $@.py; \
	else \
		echo "❌ 대상 소스 파일($@.c 또는 $@.py)을 찾을 수 없습니다."; \
	fi

# =====================================================================
# [기능 2] C 언어 자동 채점 및 AddressSanitizer 컴파일 (make <파일명.c>)
# =====================================================================
%.c: FORCE
	@echo "[1] C 소스코드 컴파일 진행 중: $@ (ASan 및 디버깅 심볼 적용)"
	gcc $@ -o main -Wall -Wextra -g -fsanitize=address
	@if [ -f data/$*.in ] && [ -f data/$*.out ]; then \
		echo "[2] 자동 테스트 모드 진입 (제한 시간: 2초)"; \
		timeout 2s ./main < data/$*.in > data/$*.res; \
		STATUS=$$?; \
		if [ $$STATUS -eq 124 ]; then \
			echo "❌ 결과: 시간 초과 (Time Limit Exceeded) - 무한 루프가 의심됩니다!"; \
		elif [ $$STATUS -ne 0 ]; then \
			echo "❌ 결과: 런타임 에러 또는 메모리 결함 발생! (Exit Code: $$STATUS)"; \
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
			echo ""; \
			echo "=================================================="; \
			echo " 🔍 틀린 위치 분석 (Word-level Diff)"; \
			echo "    (빨간색 [-값-] : 누락된 정답 / 초록색 {+값+} : 잘못 출력한 내 값)"; \
			echo "--------------------------------------------------"; \
			git --no-pager diff --no-index --word-diff=color data/$*.out data/$*.res || true; \
			echo ""); \
		fi; \
		rm -f data/$*.res main; \
		exit $$STATUS; \
	else \
		echo "[2] 테스트 파일 누락. 일반 실행 모드로 진입합니다."; \
		./main; \
		STATUS=$$?; \
		rm -f main; \
		exit $$STATUS; \
	fi

# =====================================================================
# [기능 3] Python 스크립트 자동 채점 (make <파일명.py>)
# =====================================================================
%.py: FORCE
	@echo "[1] 파이썬 스크립트 실행 준비: $@"
	@if [ -f data/$*.in ] && [ -f data/$*.out ]; then \
		echo "[2] 자동 테스트 모드 진입 (제한 시간: 2초)"; \
		timeout 2s python3 $@ < data/$*.in > data/$*.res; \
		STATUS=$$?; \
		if [ $$STATUS -eq 124 ]; then \
			echo "❌ 결과: 시간 초과 (Time Limit Exceeded) - 무한 루프가 의심됩니다!"; \
		elif [ $$STATUS -ne 0 ]; then \
			echo "❌ 결과: 런타임 에러 발생! (Exit Code: $$STATUS)"; \
			echo "   -> ⚠️ 위의 파이썬 Traceback 에러 메시지를 확인하세요."; \
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
			echo ""; \
			echo "=================================================="; \
			echo " 🔍 틀린 위치 분석 (Word-level Diff)"; \
			echo "    (빨간색 [-값-] : 누락된 정답 / 초록색 {+값+} : 잘못 출력한 내 값)"; \
			echo "--------------------------------------------------"; \
			git --no-pager diff --no-index --word-diff=color data/$*.out data/$*.res || true; \
			echo ""); \
		fi; \
		rm -f data/$*.res; \
		exit $$STATUS; \
	else \
		echo "[2] 테스트 파일 누락. 일반 실행 모드로 진입합니다."; \
		python3 $@; \
		STATUS=$$?; \
		exit $$STATUS; \
	fi