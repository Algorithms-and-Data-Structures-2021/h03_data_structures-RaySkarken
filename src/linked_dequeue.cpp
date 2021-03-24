#include "linked_dequeue.hpp"

#include <stdexcept>  // logic_error

namespace itis {

void LinkedDequeue::Enqueue(Element e) {
  if (size_ == 0) {
      front_ = new DoublyNode(e, nullptr, nullptr);
      back_ = front_;
  } else {
      back_->next = new DoublyNode(e, back_, nullptr);
      back_ = back_->next;
  }
  size_ += 1;
}

void LinkedDequeue::EnqueueFront(Element e) {
    if (size_ == 0) {
        front_ = new DoublyNode(e, nullptr, nullptr);
        back_ = front_;
    } else {
        front_->previous = new DoublyNode(e, nullptr, front_);
        front_ = front_->previous;
    }
    size_ += 1;
}

void LinkedDequeue::Dequeue() {
  if (size_ == 0) {
    throw std::logic_error("cannot not dequeue from empty queue");
  }
  if (size_ >= 2) {
      front_ = front_->next;
      delete front_->previous;
      front_->previous = nullptr;
  } else {
      delete front_;
      front_ = nullptr;
      back_ = nullptr;
  }
  size_ -= 1;
}

void LinkedDequeue::DequeueBack() {
  if (size_ == 0) {
    throw std::logic_error("cannot not dequeue from empty queue");
  }

  if (size_ >= 2) {
      back_ = back_->previous;
      delete back_->next;
      back_->next = nullptr;
  } else {
      delete back_;
      front_ = nullptr;
      back_ = nullptr;
  }
  size_ -= 1;
}

void LinkedDequeue::Clear() {
  // TODO: напишите здесь свой код ...
  while (size_ > 0) {
      Dequeue();
  }

}

// === РЕАЛИЗОВАНО ===

LinkedDequeue::~LinkedDequeue() {
  Clear();
}

std::optional<Element> LinkedDequeue::front() const {
  return front_ == nullptr ? std::nullopt : std::make_optional(front_->data);
}

std::optional<Element> LinkedDequeue::back() const {
  return back_ == nullptr ? std::nullopt : std::make_optional(back_->data);
}

bool LinkedDequeue::IsEmpty() const {
  return size_ == 0;
}

int LinkedDequeue::size() const {
  return size_;
}

// === НЕОБХОДИМО ДЛЯ ТЕСТИРОВАНИЯ ===

std::ostream &operator<<(std::ostream &os, const LinkedDequeue &queue) {
  os << "size: " << queue.size_ << '\n';
  for (auto current_node = queue.front_; current_node != nullptr; current_node = current_node->previous) {
    if (current_node == queue.front_) os << "[FRONT] ";
    if (current_node == queue.back_) os << "[BACK] ";
    os << enum2str(current_node->data) << '\n';
  }
  return os;
}

}  // namespace itis
