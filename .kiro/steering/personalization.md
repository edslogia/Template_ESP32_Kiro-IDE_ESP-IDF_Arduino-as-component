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

### Adaptive Learning Memory

- **Learning Progress**: Not initialized
- **Mastered Concepts**: []
- **Current Learning Focus**: Not set
- **Interaction History**: []

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
- **Adaptive**: Reduce detail as concepts are mastered

### For Intermedio C++ Users:

- Focus on ESP32-specific C++ best practices
- Explain ESP-IDF integration patterns
- Highlight performance and memory considerations
- **Adaptive**: Introduce advanced concepts when ready

### For Avanzado C++ Users:

- Assume C++ knowledge, focus on ESP32 specifics
- Provide concise, technical explanations
- Emphasize advanced ESP-IDF features and optimizations
- **Adaptive**: Challenge with cutting-edge implementations

### For Different ESP32 Experience Levels:

- **Principiante**: Explain hardware concepts, GPIO, FreeRTOS basics
- **Intermedio**: Focus on ESP-IDF vs Arduino differences, advanced features
- **Avanzado**: Assume ESP-IDF knowledge, focus on specific implementation details
- **Adaptive**: Automatically adjust based on demonstrated competency

### For Different AI Collaboration Levels:

- **Principiante**: Ask for confirmation before major changes, explain each step
- **Intermedio**: Provide code with explanations, ask for feedback
- **Avanzado**: Generate code efficiently, provide minimal explanations unless requested
- **Adaptive**: Evolve collaboration style based on user success patterns

### Adaptive Learning Behaviors:

#### When User Masters a Concept:

1. **Notification**: "I'm updating your personalization profile to reflect your mastery of [concept]"
2. **Behavior Change**: Reduce explanations for that concept in future interactions
3. **Progression**: Introduce related advanced topics
4. **Memory Update**: Add to mastered concepts list with timestamp

#### When User Struggles:

1. **Detection**: Multiple questions or errors on same topic
2. **Adaptation**: Increase explanation detail and provide more examples
3. **Focus**: Prioritize assistance on struggling areas
4. **Memory Update**: Add to current learning focus

#### Experience Level Promotion:

- **Automatic**: When user demonstrates consistent mastery across multiple concepts
- **Notification**: "Based on your progress, I'm updating your experience level from [old] to [new]"
- **Gradual**: Smooth transition with option to revert if too advanced

## Adaptive Learning System

### Learning Detection Triggers

The AI assistant will automatically detect learning progress and update the personalization profile when:

1. **Explicit Learning Statements**: User says things like:

   - "I understand now how FreeRTOS tasks work"
   - "I've learned about GPIO configuration"
   - "I now know how to use ESP-IDF components"
   - "I mastered the Arduino integration"

2. **Behavioral Learning Indicators**: AI detects when user:

   - Successfully implements concepts without assistance
   - Asks more advanced questions about previously explained topics
   - Corrects or improves AI-suggested code
   - Demonstrates understanding through code modifications

3. **Progress Milestones**: Automatic detection of:
   - First successful build and flash
   - First custom component creation
   - First advanced ESP-IDF feature usage
   - First independent troubleshooting

### Learning Memory Structure

```json
{
  "masteredConcepts": [
    {
      "concept": "FreeRTOS Tasks",
      "dateAchieved": "2025-01-31",
      "confidenceLevel": "high",
      "context": "Successfully created custom task for LED control"
    }
  ],
  "learningProgress": {
    "currentFocus": "WiFi Integration",
    "strugglingWith": ["Memory Management"],
    "recentAchievements": ["GPIO Configuration", "Serial Communication"]
  },
  "interactionHistory": [
    {
      "date": "2025-01-31",
      "topic": "Arduino Integration",
      "outcome": "mastered",
      "notes": "User successfully implemented without guidance"
    }
  ]
}
```

### Adaptive Behavior Changes

Based on learning progress, the AI will:

1. **Reduce Explanations**: For mastered concepts, provide less detailed explanations
2. **Increase Complexity**: Suggest more advanced implementations for understood topics
3. **Focus Assistance**: Concentrate help on areas where user is still learning
4. **Update Experience Level**: Automatically promote user experience levels when appropriate
5. **Personalize Examples**: Use examples that build on previously mastered concepts

### Learning Update Notifications

**IMPORTANT**: The AI assistant MUST always notify the user when updating the personalization file:

- "I'm updating your personalization profile to reflect that you've mastered [concept]"
- "I notice you've learned [topic], so I'm updating your learning progress"
- "Based on your recent success with [feature], I'm adjusting your assistance level"

## How to Update This Profile

Users can request profile updates at any time by saying:

- "Update my personalization preferences"
- "Change my experience level to..."
- "I want more/less detailed comments"
- "Switch to English/Spanish comments"
- "I've learned [specific concept]"
- "I'm struggling with [specific topic]"
- "Reset my learning progress"

The AI assistant will then update this file accordingly and apply the new preferences immediately.

### Manual Learning Updates

Users can explicitly update their learning progress:

- "Mark [concept] as mastered"
- "I need more help with [topic]"
- "I'm ready for more advanced [subject] examples"
- "Remove [concept] from my mastered list"
