# 명령줄에 입력된 타겟들(예: test.c)을 모두 가짜 타겟(PHONY)으로 지정하여 파일 존재 여부와 무관하게 무조건 실행되도록 강제함
.PHONY: help $(MAKECMDGOALS)

# 인자 없이 make만 입력했을 때의 기본 동작
help:
	@echo "사용법: make <파일명.c>"

# .c 로 끝나는 모든 입력에 대해 동작하는 패턴 규칙
%.c:
	gcc $@ -o main
	./main