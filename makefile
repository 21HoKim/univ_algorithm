.PHONY: FORCE

# 'week'로 끝나는 모든 입력(예: 4week, 5week)을 가로채는 패턴 규칙
%week: FORCE
	@echo "🚀 [$@] 주차 작업 환경(Scaffolding) 구축을 시작합니다..."
	
	@# 1. 대상 디렉토리 및 하위 data 폴더 생성 (-p 옵션으로 멱등성 보장)
	mkdir -p $@/data
	
	@# 2. 기존에 완성해둔 3week(sort)의 makefile을 새 디렉토리로 복사
	@# (만약 원본 경로가 다르다면 알맞게 수정해 주세요)
	cp "3week(sort)/makefile" $@/makefile
	
	@echo "✅ [$@] 폴더, data 디렉토리, makefile 세팅이 완료되었습니다!"