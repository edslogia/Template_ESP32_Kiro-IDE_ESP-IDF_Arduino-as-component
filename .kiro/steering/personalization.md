# User Personalization Profile

## Instructions for AI Assistant

This file contains the user's personalization preferences for this ESP32 project. These settings should be applied consistently across all interactions to provide tailored assistance.

**IMPORTANT RULES:**
1. **One-time setup**: The personalization questions should only be asked ONCE when this file doesn't exist or is empty
2. **Persistent storage**: All personalization data must be stored in this file and referenced in future chats
3. **User control**: The user can modify these preferences at any time by asking you to update this file
4. **AI responsibility**: You (the AI assistant) must update this steering file whenever the user requests changes to their preferences

## Current User Profile

**Status**: Not configured
**Last Updated**: Not set

### Experience Levels
- **C++ Experience**: Not set
- **ESP32/ESP-IDF Experience**: Not set  
- **AI Collaboration Experience**: Not set

### Preferences
- **Comment Style**: Not set
- **Language Preference**: Not set

## Personalization Options Reference

### 1. C++ Experience Levels
- `principiante` - New to C++, needs detailed syntax and concept explanations
- `intermedio` - Knows basic C++, wants to learn best practices
- `avanzado` - Masters C++, only needs ESP32-specific context help

### 2. ESP32/ESP-IDF Experience Levels
- `principiante` - First time with microcontrollers or ESP32
- `intermedio` - Used Arduino IDE, but ESP-IDF is new
- `avanzado` - Knows ESP-IDF, only needs help with specific integrations

### 3. AI Collaboration Experience Levels
- `principiante` - Prefers step-by-step instructions and confirmations
- `intermedio` - Can review generated code but needs explanations
- `avanzado` - Trusts reviewing and modifying generated code independently

### 4. Comment Style Preferences
- `detallado` - Explanatory comments for each important section
- `moderado` - Comments for complex logic and main functions
- `mínimo` - Only comments for non-obvious or hardware-specific code

### 5. Language Preferences
- `español` - Comments and explanations in Spanish
- `inglés` - Comments and explanations in English
- `mixto` - Technical comments in English, explanations in Spanish

## AI Behavior Guidelines Based on Profile

### For Principiante C++ Users:
- Include detailed explanations of C++ syntax and concepts
- Explain memory management and object-oriented principles
- Provide step-by-step breakdowns of complex code

### For Intermedio C++ Users:
- Focus on ESP32-specific C++ best practices
- Explain ESP-IDF integration patterns
- Highlight performance and memory considerations

### For Avanzado C++ Users:
- Assume C++ knowledge, focus on ESP32 specifics
- Provide concise, technical explanations
- Emphasize advanced ESP-IDF features and optimizations

### For Different ESP32 Experience Levels:
- **Principiante**: Explain hardware concepts, GPIO, FreeRTOS basics
- **Intermedio**: Focus on ESP-IDF vs Arduino differences, advanced features
- **Avanzado**: Assume ESP-IDF knowledge, focus on specific implementation details

### For Different AI Collaboration Levels:
- **Principiante**: Ask for confirmation before major changes, explain each step
- **Intermedio**: Provide code with explanations, ask for feedback
- **Avanzado**: Generate code efficiently, provide minimal explanations unless requested

## How to Update This Profile

Users can request profile updates at any time by saying:
- "Update my personalization preferences"
- "Change my experience level to..."
- "I want more/less detailed comments"
- "Switch to English/Spanish comments"

The AI assistant will then update this file accordingly and apply the new preferences immediately.