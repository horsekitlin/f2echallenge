# Task
```json
{
  "todos"
    - array
    - todoItems
    - item
      processingTime
        - number
        - 已經處理的時間
        - 秒
        - default: 0
      - status
        - string
        - 狀態
        - enums
          - todo
          - processing
          - hold
          - done
      - priority
        - string
        - enums
          - low - 低
          - mid - 中
          - high - 高
          - urgent - 緊急
      - title
        - string
        - 標題
      - content
        - string
        - 內容
      - annotation
        - string
        - 備註
}
```